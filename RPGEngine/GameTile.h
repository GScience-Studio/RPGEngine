#pragma once

#include "TileTemplate.h"
#include "Renderable.h"

class GameMap;

class GameTile :public Renderable
{
	friend class GameMap;

	//!当前显示的tile id
	int mShownTileImageId = 0;

	//!当前tile的位置
	int mX = 0, mY = 0;

	//!tile模板
	const TileTemplate& mTileTemplate;

	//!从tile模板创建tile
	explicit GameTile(const TileTemplate& tileTemplate) :mTileTemplate(tileTemplate) {}

public:
	void draw(SDL_Renderer* renderer) override;
	void refresh(double passedTick) override;
};
