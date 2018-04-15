#include "GameScene.h"
#include "../Engine.h"
#include <SDL2/SDL.h>

void GameScene::draw(SDL_Renderer* renderer, int xOffset, int yOffset)
{
	auto& cameraLocation = mCamera.getLocation();

	if (!cameraLocation.inMap)
		return;

	//把地图左上角挪到屏幕中央后再根据相机偏移计算地图渲染位置
	cameraLocation.inMap->draw(renderer,
		static_cast<int>((-cameraLocation.x + CENTET_TILE_X) * TILE_SIZE),
		static_cast<int>((-cameraLocation.y + CENTET_TILE_Y) * TILE_SIZE)
	);

	//绘制玩家
	GamePlayer::getGlobalPlayer().draw(renderer, 
		static_cast<int>((-cameraLocation.x + CENTET_TILE_X) * TILE_SIZE),
		static_cast<int>((-cameraLocation.y + CENTET_TILE_Y) * TILE_SIZE)
	);
}

void GameScene::refresh(double passedTick)
{
	//刷新地图
	mCamera.getLocation().inMap->refresh(passedTick);

	//刷新玩家
	GamePlayer::getGlobalPlayer().refresh(passedTick);

	//处理交互事件
	if (mActions.empty())
	{
		const auto keysState = SDL_GetKeyboardState(nullptr);

		auto& player = GamePlayer::getGlobalPlayer();

		if (keysState[SDL_SCANCODE_UP])
			addAction<ActorLinearMoveAction>(&player, ActorAppearance::FaceBack, 1, 0.5);
		else if (keysState[SDL_SCANCODE_DOWN])
			addAction<ActorLinearMoveAction>(&player, ActorAppearance::FaceFront, 1, 0.5);
		else if (keysState[SDL_SCANCODE_LEFT])
			addAction<ActorLinearMoveAction>(&player, ActorAppearance::FaceLeft, 1, 0.5);
		else if (keysState[SDL_SCANCODE_RIGHT])
			addAction<ActorLinearMoveAction>(&player, ActorAppearance::FaceRight, 1, 0.5);

	}
	else
	{
		auto& action = mActions.front();
		action->refresh(passedTick);
		if (action->isFinish())
			mActions.pop();
	}
}

GameScene::GameScene(SDL_Renderer* renderer) :SceneBase(renderer), mCamera(&GamePlayer::getGlobalPlayer()) {}