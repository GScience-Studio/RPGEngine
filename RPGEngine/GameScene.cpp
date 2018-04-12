#include "GameScene.h"
#include "../Engine.h"

void GameScene::draw(SDL_Renderer* renderer, int xOffset, int yOffset)
{
	//�ѵ�ͼ���Ͻ�Ų����Ļ������ٸ������ƫ�Ƽ����ͼ��Ⱦλ��
	mCameraIn->draw(renderer, (-mCameraX + XTILE_COUNT / 2) * TILE_SIZE, (-mCameraY + YTILE_COUNT / 2) * TILE_SIZE);
}

void GameScene::refresh(double passedTick)
{
	mCameraIn->refresh(passedTick);
}