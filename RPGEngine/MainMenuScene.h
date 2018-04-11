#pragma once

#include "SceneBase.h"

class MainMenuScene :public SceneBase
{
public:
	MainMenuScene(SDL_Renderer* renderer):SceneBase(renderer)
	{
		
	}

	void draw(SDL_Renderer* renderer) override {}
	void refresh(double passedTick) override {}
};
