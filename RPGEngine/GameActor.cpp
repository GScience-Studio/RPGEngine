#include "GameActor.h"
#include "../Engine.h"
#include "GameMap.h"
#include <SDL2/SDL.h>
#include <iostream>

void RenderableGameActor::draw(SDL_Renderer* renderer, int xOffset, int yOffset)
{
	if (!mRenderableActorTemplate)
		return;

	const auto texture = mRenderableActorTemplate->actorWalkingImage[mDirection][mAnimationId];

	std::cout << mAnimationId << std::endl;

	SDL_Rect renderPos;
	renderPos.x = static_cast<int>(xOffset + x * TILE_SIZE);
	renderPos.y = static_cast<int>(yOffset + (y - 1) * TILE_SIZE);
	renderPos.h = ACTOR_HEIGHT;
	renderPos.w = ACTOR_WIDTH;

	SDL_RenderCopy(renderer, texture, nullptr, &renderPos);
}

void RenderableGameActor::refresh(double passedTick)
{
	//判断是否需要处理动画
	if (!mIsPlayingAnimation && mAnimationId == 0)
		return;

	//判断是否到达延迟
	if ((mWaitedTime += passedTick) < mAnimationSpeed)
		return;

	mWaitedTime -= mAnimationSpeed;
	++mAnimationId;

	if (mAnimationId >= mRenderableActorTemplate->actorWalkingImage[mDirection].size())
		mAnimationId = 0;
}

void Camera::refresh()
{
	inMap = mActor->inMap;
	x = mActor->x;
	y = mActor->y;

	//尽量多显示地图处理

	//x居中
	if (inMap->width <= XTILE_COUNT)
		x = (inMap->width + 1) / 2.0 - 1;
	//x限制相机在可视范围内
	else
		if (x <= CENTET_TILE_X)
			x = CENTET_TILE_X;
		else if (inMap->width - x <= XTILE_COUNT - CENTET_TILE_X)
			x = inMap->width - XTILE_COUNT + CENTET_TILE_X;

	//y居中
	if (inMap->height <= YTILE_COUNT)
		y = (inMap->height + 1) / 2.0 - 1;
	//y限制相机在可视范围内
	else
		if (y <= CENTET_TILE_Y)
			y = CENTET_TILE_Y;
		else if ((inMap->height - 1) - y <= YTILE_COUNT - CENTET_TILE_Y)
			y = inMap->height - (YTILE_COUNT - CENTET_TILE_Y + 1);
}