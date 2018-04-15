#pragma once

class GameMap;

/*!负责处理地图事件
 * 建议为每个地图定义一个基于GameMapEventProcessorBase的类并在创建地图时传入
 */
class GameMapEventProcessorBase
{
public:
	//!当玩家移动时调用
	virtual void onPlayerMove(int toX, int toY) {};
	//!当玩家和地图交互时调用，可以获取到玩家的位置和交互的位置
	virtual void onPlayerInteractTile(int playerX, int playerY, int x, int y) {};
	
	//!当玩家和actor交互时调用，可以获取到玩家的位置和交互actor的位置
	virtual void onPlayerInteractActor(const char* actorName, int playerX, int playerY, int x, int y) {};
	//!当玩家进入Actor视野时调用，可以获取到玩家的位置和交互actor的位置
	virtual void onPlayerMoveInActorSight(const char* actorName, int playerX, int playerY, int x, int y) {};

	//!当地图初始化的时候，即程序启动的时候
	virtual void onInitMap(GameMap* gameMap) {};

	virtual ~GameMapEventProcessorBase() = default;
};