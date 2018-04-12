#pragma once

class GameMap;

class GameMapEventProcessorBase
{
public:
	//!当玩家移动时调用
	virtual void onPlayerMove(GameMap* gameMap, int toX, int toY) = 0;
	//当玩家和地图交互时调用，可以获取到玩家的位置和交互的位置
	virtual void onPlayerInteractTile(GameMap* gameMap, int playerX, int playerY, int x, int y) = 0;
	
	//当玩家和actor交互时调用，可以获取到玩家的位置和交互actor的位置
	virtual void onPlayerInteractActor(GameMap* gameMap, int playerX, int playerY, int x, int y) = 0;
	//当玩家进入Actor视野时调用，可以获取到玩家的位置和交互actor的位置
	virtual void onPlayerMoveInActorSight(GameMap* gameMap, int playerX, int playerY, int x, int y) = 0;

	virtual ~GameMapEventProcessorBase() = default;
};