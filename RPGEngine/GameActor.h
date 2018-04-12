#pragma once

#include "Renderable.h"

class GameMap;

class GameActor
{
public:
	double x = 0, y = 0;
	GameMap* inMap = nullptr;
};

//!ø…‰÷»æµƒactor
class RenderableGameActor :public GameActor, public Renderable
{
public:
	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override {}
	void refresh(double passedTick) override {}
};

class GamePlayer :public RenderableGameActor
{
	GamePlayer() = default;

public:
	static GamePlayer& getGlobalPlayer()
	{
		static GamePlayer player;
		return player;
	}
};

using Camera = GameActor;