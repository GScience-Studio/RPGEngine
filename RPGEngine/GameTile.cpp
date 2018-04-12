#include "GameTile.h"
#include "../Engine.h"
#include <SDL2/SDL.h>

void GameTile::draw(SDL_Renderer* renderer, const int xOffset, const int yOffset)
{
	const auto texture = mTileTemplate.tileImageList[mShownTileImageId];

	SDL_Rect renderPos;
	renderPos.x = xOffset;
	renderPos.y = yOffset;
	renderPos.h = TILE_SIZE;
	renderPos.w = TILE_SIZE;

	SDL_RenderCopy(renderer, texture, nullptr, &renderPos);
}

void GameTile::refresh(double passedTick)
{
	
}