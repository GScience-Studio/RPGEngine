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

		//地图尺寸信息
		height = root["height"].asInt();
		width = root["width"].asInt();

		mMapData.resize(width);
		for (auto& column: mMapData)
			column.resize(height);

		//tile索引
		//0号为空白
		std::vector<const TileTemplate*> tileTemplateIndex;
		tileTemplateIndex.emplace_back(nullptr);
		for (auto& tileIndex : root["tile_list"])
			tileTemplateIndex.emplace_back(&TileTemplate::getTileTemplate(tileIndex["tile_name"].asCString()));

		//加载地图数据
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

		//加载所有actor
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

		//调用初始化事件
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
	//逐level绘制
	unsigned int level = 0;
	auto hasItem = true;

	//没绘制的actor
	std::vector<std::shared_ptr<GameActor>> unrenderedActorList;
	for (auto& actor : actorList)
		unrenderedActorList.push_back(actor.second);

	while (hasItem)
	{
		hasItem = false;

		//绘制地图
		for (auto x = 0; x != width; ++x)
			for (auto y = 0; y != height; ++y)
			{
				//本level是否有需要绘制的
				if (mMapData[x][y].size() > level)
				{
					mMapData[x][y][level]->draw(renderer, xOffset + x * TILE_SIZE, yOffset + y * TILE_SIZE);

					//那么下一level呢
					if (mMapData[x][y].size() > level + 1)
						hasItem = true;
				}
			}

		//绘制actor
		auto actor = unrenderedActorList.begin();
		do
		{
			//是否满足高度要求
			if ((*actor)->level > level)
				continue;

			//是否超过高度要求
			if ((*actor)->level + ACTOR_HEIGHT / TILE_SIZE < level)
			{
				actor = unrenderedActorList.erase(actor);
				continue;
			}

			//绘制
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
	//刷新Actor
	for (auto& actor : actorList)
		actor.second->refresh(passedTick);
	
	//刷新tile
	for (auto tileVector1 : mMapData)
		for (auto& tileVector2 : tileVector1)
			for (auto& tile : tileVector2)
				tile->refresh(passedTick);
}