#include "GameScene.h"
#include "../Engine.h"

void GameScene::draw(SDL_Renderer* renderer, int xOffset, int yOffset)
{
	//把地图左上角挪到屏幕中央后再根据相机偏移计算地图渲染位置
	mCameraIn->draw(renderer, (-mCameraX + XTILE_COUNT / 2) * TILE_SIZE, (-mCameraY + YTILE_COUNT / 2) * TILE_SIZE);
}

void GameScene::refresh(double passedTick)
{
	mCameraIn->refresh(passedTick);
}