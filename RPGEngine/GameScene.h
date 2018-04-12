#pragma once

#include "SceneBase.h"
#include "GameMap.h"

class GameScene :public SceneBase
{
	GameMap* mCameraIn = nullptr;
	int mCameraX = 0;
	int mCameraY = 0;

public:
	explicit GameScene(SDL_Renderer* renderer) :SceneBase(renderer) {}

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;

	/*!�������λ��
	 * @note ��������ǹ��ڵ�ͼ������
	 */
	void setCamera(GameMap* map, const int cameraX, const int cameraY)
	{
		mCameraIn = map;
		mCameraX = cameraX;
		mCameraY = cameraY;
	}
};
