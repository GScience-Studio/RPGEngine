#pragma once

#include "TileTemplate.h"
#include "Renderable.h"

class GameMap;

class GameTile :public Renderable
{
	friend class GameMap;

	//!��ǰ��ʾ��tile id
	int mShownTileImageId = 0;

	//!��ǰtile��λ��
	int mX = 0, mY = 0;

	//!tileģ��
	const TileTemplate& mTileTemplate;

	//!��tileģ�崴��tile
	explicit GameTile(const TileTemplate& tileTemplate) :mTileTemplate(tileTemplate) {}

public:
	void draw(SDL_Renderer* renderer) override;
	void refresh(double passedTick) override;
};
