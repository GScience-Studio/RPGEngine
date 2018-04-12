#pragma once

#include "SceneBase.h"
#include "GameMap.h"
#include "GameAction.h"
#include "GameActor.h"
#include <queue>

class GameScene :public SceneBase
{
	Camera mCamera;

	//!�Ƿ������󶨵��������
	bool mIsBindCameraToPlayer = true;

	//!��¼����action
	std::queue<std::unique_ptr<GameAction>> mActions;

public:
	explicit GameScene(SDL_Renderer* renderer) :SceneBase(renderer) {}

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;

	/*!�������λ��
	 * @note ��������ǹ��ڵ�ͼ������
	 */
	void setCamera(GameMap* map, const int cameraX, const int cameraY)
	{
		mCamera.inMap = map;
		mCamera.x = cameraX;
		mCamera.y = cameraY;
	}

	template<class action, class... t> void addAction(t... data)
	{
		mActions.emplace(std::make_unique<action>(data...));
	}
};
