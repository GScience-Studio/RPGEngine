#include "GameScene.h"
#include "../Engine.h"
#include <SDL2/SDL.h>

void GameScene::draw(SDL_Renderer* renderer, int xOffset, int yOffset)
{
	if (!mCamera.inMap)
		return;

	//把地图左上角挪到屏幕中央后再根据相机偏移计算地图渲染位置
	mCamera.inMap->draw(renderer, 
		static_cast<int>((-mCamera.x + XTILE_COUNT / 2.0) * TILE_SIZE), 
		static_cast<int>((-mCamera.y + YTILE_COUNT / 2.0) * TILE_SIZE)
	);
}

void GameScene::refresh(double passedTick)
{
	if (mIsBindCameraToPlayer)
	{
		auto& player = GamePlayer::getGlobalPlayer();
		mCamera.inMap = player.inMap;
		mCamera.x = player.x;
		mCamera.y = player.y;
	}

	mCamera.inMap->refresh(passedTick);

	if (mActions.empty())
	{
		const auto keysState = SDL_GetKeyboardState(nullptr);

		auto& player = GamePlayer::getGlobalPlayer();

		if (keysState[SDL_SCANCODE_UP])
			addAction<ActorMoveAction>(&player, player.x, player.y - 1, 0.25);
		else if (keysState[SDL_SCANCODE_DOWN])
			addAction<ActorMoveAction>(&player, player.x, player.y + 1, 0.25);
		else if (keysState[SDL_SCANCODE_LEFT])
			addAction<ActorMoveAction>(&player, player.x - 1, player.y, 0.25);
		else if (keysState[SDL_SCANCODE_RIGHT])
			addAction<ActorMoveAction>(&player, player.x + 1, player.y, 0.25);

	}
	else
	{
		auto& action = mActions.front();
		action->refresh(passedTick);
		if (action->isFinish())
			mActions.pop();
	}
}