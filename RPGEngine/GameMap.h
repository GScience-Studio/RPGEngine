#pragma once

#include "GameTile.h"

class GameMap :public Renderable
{
	static std::map<std::string, std::unique_ptr<GameMap>>& getGameMapMap()
	{
		static std::map<std::string, std::unique_ptr<GameMap>> gameMapMap;
		return gameMapMap;
	}

	//[X][Y][Level]
	std::vector<std::vector<std::vector<std::unique_ptr<GameTile>>>> mMapData;

public:
	//����һ����Ϸ��ͼ
	GameMap(SDL_Renderer* renderer, const char* mapName, std::string json);

	//��ͼ�Ĵ�С
	int height, width;

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override {}

	static void registerGameMap(SDL_Renderer* renderer, const char* mapName, const std::string& json)
	{
		getGameMapMap()[mapName] = std::make_unique<GameMap>(renderer, mapName, json);
	}

	static GameMap& getGameMap(const char* tileName)
	{
		return *getGameMapMap()[tileName];
	}
};