#include "GameActor.h"
#include "../Engine.h"
#include "GameMap.h"
#include <SDL2/SDL.h>
#include <iostream>

void GameActor::draw(SDL_Renderer* renderer, const int xOffset, const int yOffset)
{
	if (!mRenderableActorTemplate)
		return;

	const auto texture = mRenderableActorTemplate->actorWalkingImage[mDirection][mAnimationId];

	std::cout << mAnimationId << std::endl;

	SDL_Rect renderPos;
	renderPos.x = static_cast<int>(xOffset + location.x * TILE_SIZE);
	renderPos.y = static_cast<int>(yOffset + (location.y - 1) * TILE_SIZE);
	renderPos.h = ACTOR_HEIGHT;
	renderPos.w = ACTOR_WIDTH;

	SDL_RenderCopy(renderer, texture, nullptr, &renderPos);
}

void GameActor::refresh(const double passedTick)
{
	//�ж��Ƿ���Ҫ������
	if (!mIsPlayingAnimation && mAnimationId == 0)
		return;

	//�ж��Ƿ񵽴��ӳ�
	if ((mWaitedTime += passedTick) < mAnimationSpeed)
		return;

	mWaitedTime -= mAnimationSpeed;
	++mAnimationId;

	if (mAnimationId >= mRenderableActorTemplate->actorWalkingImage[mDirection].size())
		mAnimationId = 0;
}

void Camera::refresh()
{
	mLocation.inMap = mActor->location.inMap;
	mLocation.x = mActor->location.x;
	mLocation.y = mActor->location.y;

	//��������ʾ��ͼ����

	//x����
	if (mLocation.inMap->width <= XTILE_COUNT)
		mLocation.x = (mLocation.inMap->width + 1) / 2.0 - 1;
	//x��������ڿ��ӷ�Χ��
	else
		if (mLocation.x <= CENTET_TILE_X)
			mLocation.x = CENTET_TILE_X;
		else if (mLocation.inMap->width - mLocation.x <= XTILE_COUNT - CENTET_TILE_X)
			mLocation.x = mLocation.inMap->width - XTILE_COUNT + CENTET_TILE_X;

	//y����
	if (mLocation.inMap->height <= YTILE_COUNT)
		mLocation.y = (mLocation.inMap->height + 1) / 2.0 - 1;
	//y��������ڿ��ӷ�Χ��
	else
		if (mLocation.y <= CENTET_TILE_Y)
			mLocation.y = CENTET_TILE_Y;
		else if ((mLocation.inMap->height - 1) - mLocation.y <= YTILE_COUNT - CENTET_TILE_Y)
			mLocation.y = mLocation.inMap->height - (YTILE_COUNT - CENTET_TILE_Y + 1);
}