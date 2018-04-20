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
	std::vector<std::vector<std::vector<std::shared_ptr<GameTile>>>> mMapData;

	const GameMapEventProcessorBase* mEventProcessor;

public:
	//!��ɫ��
	std::map<std::string, std::shared_ptr<GameActor>> actorList;

	//!����һ��actor
	GameActor* addActor(const char* name, const char* appearance);

	//!����һ����Ϸ��ͼ
	GameMap(SDL_Renderer* renderer, const char* mapName, std::string json, GameMapEventProcessorBase* eventProcessor);

	//!��ȡָ��λ�õ�Tile��Ϣ
	std::vector<std::shared_ptr<GameTile>> getTiles(const int x, const int y) const
	{
		std::vector<std::shared_ptr<GameTile>> tiles;

		for (auto& tile : mMapData[x][y])
			tiles.emplace_back(tile);

		return tiles;
	}

	//!��ȡ����Actor
	std::vector<std::shared_ptr<GameActor>> getActors() const
	{
		std::vector<std::shared_ptr<GameActor>> actors;

		for (auto& actor : actorList)
			actors.emplace_back(actor.second);

		return actors;
	}

	//!��ͼ�Ĵ�С
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