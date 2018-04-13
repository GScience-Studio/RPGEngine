#pragma once

#include "TileTemplate.h"
#include "Renderable.h"

class GameMap;

class GameTile :public Renderable
{
	//!当前显示的tile id
	int mShownTileImageId = 0;

	//!tile模板
	const TileTemplate* mTileTemplate;

public:
	//!从tile模板创建tile
	explicit GameTile(const TileTemplate* tileTemplate) :mTileTemplate(tileTemplate) {}

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;
};
