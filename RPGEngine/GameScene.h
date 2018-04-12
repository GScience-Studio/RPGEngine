#pragma once

#include "SceneBase.h"
#include "GameMap.h"
#include "GameAction.h"
#include "GameActor.h"
#include <queue>

class GameScene :public SceneBase
{
	Camera mCamera;

	//!是否把相机绑定到玩家身上
	bool mIsBindCameraToPlayer = true;

	//!记录所有action
	std::queue<std::unique_ptr<GameAction>> mActions;

public:
	explicit GameScene(SDL_Renderer* renderer) :SceneBase(renderer) {}

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;

	/*!设置相机位置
	 * @note 相机坐标是关于地图的坐标
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
