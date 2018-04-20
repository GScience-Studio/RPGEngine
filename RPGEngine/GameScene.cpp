#include "GameScene.h"
#include "../Engine.h"
#include "GameTile.h"
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
}

void GameScene::refresh(const double passedTick)
{
	//刷新地图
	mCamera.getLocation().inMap->refresh(passedTick);

	//处理交互事件
	if (mActions.empty())
	{
		const auto keysState = SDL_GetKeyboardState(nullptr);

		auto& player = GamePlayer::getGlobalPlayer();

		const auto canMoveTo = [&](GameMap* gameMap, int x, int y)
		{
			//超越地图
			if (x < 0 || y < 0 || x >= gameMap->width || y >= gameMap->height - 1)
				return false;

			//地图屏障
			auto tiles = player.getInMap()->getTiles(x, y);
			for (auto& tile : tiles)
			{
				if (tile->getTileTemplate() && tile->getTileTemplate()->tileAction == TileTemplate::Barrier)
					return false;
			}

			//角色遮挡
			for (auto& actor : player.getInMap()->getActors())
				if (actor->x == x && actor->y == y)
					return false;

			return true;
		};

		ActorAppearance::Direction direction;
		auto canMoveToTile = false;

		if (keysState[SDL_SCANCODE_UP])
		{
			canMoveToTile = canMoveTo(player.getInMap(), player.x, player.y - 1);
			direction = ActorAppearance::FaceBack;
		}
		else if (keysState[SDL_SCANCODE_DOWN])
		{
			canMoveToTile = canMoveTo(player.getInMap(), player.x, player.y + 1);
			direction = ActorAppearance::FaceFront;
		}
		else if (keysState[SDL_SCANCODE_LEFT])
		{
			canMoveToTile = canMoveTo(player.getInMap(), player.x - 1, player.y);
			direction = ActorAppearance::FaceLeft;
		}
		else if (keysState[SDL_SCANCODE_RIGHT])
		{
			canMoveToTile = canMoveTo(player.getInMap(), player.x + 1, player.y);
			direction = ActorAppearance::FaceRight;
		}

		if (canMoveToTile)
			addAction<ActorLinearMoveAction>(&player, direction, 1, 0.5);

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