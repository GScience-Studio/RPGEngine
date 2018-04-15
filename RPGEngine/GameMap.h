#pragma once

#include "GameTile.h"
#include "GameActor.h"

class GameMapEventProcessorBase;

class GameMap :public Renderable
{
	static std::map<std::string, std::unique_ptr<GameMap>>& getGameMapMap()
	{
		static std::map<std::string, std::unique_ptr<GameMap>> gameMapMap;
		return gameMapMap;
	}

	//![X][Y][Level]
	std::vector<std::vector<std::vector<std::unique_ptr<GameTile>>>> mMapData;

	const GameMapEventProcessorBase* mEventProcessor;

public:
	//!角色表
	std::map<std::string, std::shared_ptr<GameActor>> actorList;

	//!增加一个actor
	GameActor* addActor(const char* name, const char* appearance);

	//创建一个游戏地图
	GameMap(SDL_Renderer* renderer, const char* mapName, std::string json, GameMapEventProcessorBase* eventProcessor);

	//地图的大小
	int height, width;

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;

	static void registerGameMap(SDL_Renderer* renderer, const char* mapName, const std::string& json, GameMapEventProcessorBase* eventProcessor)
	{
		getGameMapMap()[mapName] = std::make_unique<GameMap>(renderer, mapName, json, eventProcessor);
	}

	static GameMap& getGameMap(const char* tileName)
	{
		return *getGameMapMap()[tileName];
	}
};