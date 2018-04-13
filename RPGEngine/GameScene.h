#pragma once

#include "SceneBase.h"
#include "GameMap.h"
#include "GameAction.h"
#include "GameActor.h"
#include <queue>

class GameScene :public SceneBase
{
	Camera mCamera;

	//!¼ÇÂ¼ËùÓÐaction
	std::queue<std::unique_ptr<GameAction>> mActions;

public:
	explicit GameScene(SDL_Renderer* renderer);

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;

	template<class action, class... t> void addAction(t... data)
	{
		mActions.emplace(std::make_unique<action>(data...));
	}
};
