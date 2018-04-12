#include "GameMap.h"
#include "../Engine.h"
#include <json/json.h>

GameMap::GameMap(SDL_Renderer* renderer, const char* mapName, std::string json)
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
		std::vector<TileTemplate*> tileTemplateIndex;
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

					TileTemplate* tileTemplate;
					if (jsonMapTileLevelData.type() == Json::stringValue)
						tileTemplate = &TileTemplate::getTileTemplate(jsonMapTileLevelData.asCString());
					else
						tileTemplate = tileTemplateIndex.at(jsonMapTileLevelData.asInt());

					mMapData[x][y][level] = std::make_unique<GameTile>(*tileTemplate);
				}
			}
	}
	catch (std::exception&)
	{
		return;
	}
}

void GameMap::draw(SDL_Renderer* renderer, const int xOffset, const int yOffset)
{
	for (auto x = 0; x != width; ++x)
		for (auto y = 0; y != height; ++y)
			for (auto& tile : mMapData[x][y])
				tile->draw(renderer, xOffset + x * TILE_SIZE, yOffset + y * TILE_SIZE);
}