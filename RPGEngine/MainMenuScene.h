#pragma once

#include "SceneBase.h"

class MainMenuScene :public SceneBase
{
public:
	MainMenuScene(SDL_Renderer* renderer):SceneBase(renderer)
	{
		
	}

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override {}
	void refresh(double passedTick) override {}
};
