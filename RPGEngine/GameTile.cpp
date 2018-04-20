#include "GameTile.h"
#include "../Engine.h"
#include <SDL2/SDL.h>

void GameTile::draw(SDL_Renderer* renderer, const int xOffset, const int yOffset)
{
	if (!mTileTemplate)
		return;

	const auto texture = mTileTemplate->tileImageList[mShownTileImageId];

	SDL_Rect renderPos;
	renderPos.x = xOffset;
	renderPos.y = yOffset;
	renderPos.h = TILE_SIZE;
	renderPos.w = TILE_SIZE;

	SDL_RenderCopy(renderer, texture, nullptr, &renderPos);
}

void GameTile::refresh(const double passedTick)
{
	//没有触发器或者只有一张image则不刷新
	if (!mChangeTileTrigger || mTileTemplate->tileImageList.empty())
		return;

	//设置下一个触发器并切换图片ID
	const auto toNextTileImage = [&]()
	{
		if (++mShownTileImageId == static_cast<int>(mTileTemplate->tileImageList.size()))
			mShownTileImageId = 0;

		mChangeTileTrigger = mTileTemplate->tileAnimationTriggerList[mShownTileImageId]->createCopy();
	};

	switch (mChangeTileTrigger->triggerType)
	{
	case TileAnimationTrigger::Delay:
	{
		const auto delatTrigger = std::static_pointer_cast<TriggerDelay>(mChangeTileTrigger);
		delatTrigger->setDelayTime(delatTrigger->getDelayTime() - passedTick);

		if (delatTrigger->getDelayTime() <= 0)
			toNextTileImage();
		break;
	}
	default:
		break;
	}
}

GameTile::GameTile(const TileTemplate* tileTemplate) :mShownTileImageId(0), mTileTemplate(tileTemplate)
{
	//设置触发器
	if (mTileTemplate && mTileTemplate->tileAnimationTriggerList[mShownTileImageId])
		mChangeTileTrigger = mTileTemplate->tileAnimationTriggerList[mShownTileImageId]->createCopy();
}