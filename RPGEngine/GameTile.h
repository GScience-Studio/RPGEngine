#pragma once

#include "TileTemplate.h"
#include "Renderable.h"

class GameMap;

class GameTile :public Renderable
{
	//!当前显示的tile id
	int mShownTileImageId;

	//!当前切换tile的触发器
	std::shared_ptr<TileAnimationTrigger> mChangeTileTrigger;

	//!tile模板
	const TileTemplate* mTileTemplate;

public:
	const TileTemplate* getTileTemplate() const
	{
		return mTileTemplate;
	}

	//!从tile模板创建tile
	explicit GameTile(const TileTemplate* tileTemplate);

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;
};
