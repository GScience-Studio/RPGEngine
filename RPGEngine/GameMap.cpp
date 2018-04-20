#include "GameMap.h"
#include "../Engine.h"
#include <json/json.h>
#include <SDL2/SDL.h>

GameMap::GameMap(SDL_Renderer* renderer, const char* mapName, std::string json, GameMapEventProcessorBase* eventProcessor) :mEventProcessor(eventProcessor)
{
	try
	{
		Json::CharReaderBuilder readerBuilder;
		auto reader = readerBuilder.newCharReader();
		Json::Value root;

		reader->parse(&json.front(), &json.back(), &root, nullptr);

		//��ͼ�ߴ���Ϣ
		height = root["height"].asInt();
		width = root["width"].asInt();

		mMapData.resize(width);
		for (auto& column: mMapData)
			column.resize(height);

		//tile����
		//0��Ϊ�հ�
		std::vector<const TileTemplate*> tileTemplateIndex;
		tileTemplateIndex.emplace_back(nullptr);
		for (auto& tileIndex : root["tile_list"])
			tileTemplateIndex.emplace_back(&TileTemplate::getTileTemplate(tileIndex["tile_name"].asCString()));

		//���ص�ͼ����
		for (auto x = 0; x != width; ++x)
			for (auto y = 0; y != height; ++y)
			{
				const auto jsonMapTileData = root["map_data"][y][x];
				const auto maxLevel = jsonMapTileData.size();
				mMapData[x][y].resize(maxLevel);

				for (unsigned int level = 0; level != maxLevel; ++level)
				{
					const auto jsonMapTileLevelData = jsonMapTileData[level];

					const TileTemplate* tileTemplate;
					if (jsonMapTileLevelData.type() == Json::stringValue)
						tileTemplate = &TileTemplate::getTileTemplate(jsonMapTileLevelData.asCString());
					else
						tileTemplate = tileTemplateIndex.at(jsonMapTileLevelData.asInt());

					mMapData[x][y][level] = std::make_shared<GameTile>(tileTemplate);
				}
			}

		//��������actor
		for (auto& actorInfo : root["actor_data"])
		{
			auto actor = addActor(actorInfo["name"].asCString(), actorInfo["appearance"].asCString());
			auto level = 1;

			if (actorInfo["location"]["level"].asString() == "top")
				level = 4;
			else if (actorInfo["location"]["level"].asString() == "ground")
				level = 1;
			else
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Actor level should be \"top\" or \"ground\"");

			actor->moveCrossMap(this, actorInfo["location"]["x"].asInt(), actorInfo["location"]["y"].asInt(), level);
		}

		//���ó�ʼ���¼�
		if (eventProcessor)
			eventProcessor->onInitMap(this);
	}
	catch (std::exception& e)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed do read map json because %s", e.what());

		return;
	}
}

void GameMap::draw(SDL_Renderer* renderer, const int xOffset, const int yOffset)
{
	//��level����
	unsigned int level = 0;
	auto hasItem = true;

	//û���Ƶ�actor
	std::vector<std::shared_ptr<GameActor>> unrenderedActorList;
	for (auto& actor : actorList)
		unrenderedActorList.push_back(actor.second);

	while (hasItem)
	{
		hasItem = false;

		//���Ƶ�ͼ
		for (auto x = 0; x != width; ++x)
			for (auto y = 0; y != height; ++y)
			{
				//��level�Ƿ�����Ҫ���Ƶ�
				if (mMapData[x][y].size() > level)
				{
					mMapData[x][y][level]->draw(renderer, xOffset + x * TILE_SIZE, yOffset + y * TILE_SIZE);

					//��ô��һlevel��
					if (mMapData[x][y].size() > level + 1)
						hasItem = true;
				}
			}

		//����actor
		auto actor = unrenderedActorList.begin();
		do
		{
			//�Ƿ�����߶�Ҫ��
			if ((*actor)->level > level)
				continue;

			//�Ƿ񳬹��߶�Ҫ��
			if ((*actor)->level + ACTOR_HEIGHT / TILE_SIZE < level)
			{
				actor = unrenderedActorList.erase(actor);
				continue;
			}

			//����
			(*actor)->draw(renderer, xOffset, yOffset, level - (*actor)->level);
		} while (actor != unrenderedActorList.end() && ++actor != unrenderedActorList.end());

		if (!unrenderedActorList.empty())
			hasItem = true;

		++level;
	}
}

GameActor* GameMap::addActor(const char* name, const char* appearance)
{
	auto newActor = std::make_shared<GameActor>(name, appearance);
	actorList[name] = newActor;
	return newActor.get();
}

void GameMap::refresh(const double passedTick)
{
	//ˢ��Actor
	for (auto& actor : actorList)
		actor.second->refresh(passedTick);
	
	//ˢ��tile
	for (auto tileVector1 : mMapData)
		for (auto& tileVector2 : tileVector1)
			for (auto& tile : tileVector2)
				tile->refresh(passedTick);
}