#pragma once

#include "GameTile.h"

class GameMap
{
public:
	//地图的大小
	const int height, width;

	//创建一个游戏地图
	GameMap(int height, int width);
};