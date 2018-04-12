#pragma once

#include "TileTemplate.h"
#include "Renderable.h"

class GameMap;

class GameTile :public Renderable
{
	//!��ǰ��ʾ��tile id
	int mShownTileImageId = 0;

	//!tileģ��
	const TileTemplate& mTileTemplate;

public:
	//!��tileģ�崴��tile
	explicit GameTile(const TileTemplate& tileTemplate) :mTileTemplate(tileTemplate) {}

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;
};
