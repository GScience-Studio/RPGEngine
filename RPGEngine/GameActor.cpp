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
	inMap = mActor->inMap;
	x = mActor->x;
	y = mActor->y;

	//��������ʾ��ͼ����

	//x����
	if (inMap->width <= XTILE_COUNT)
		x = (inMap->width + 1) / 2.0 - 1;
	//x��������ڿ��ӷ�Χ��
	else
		if (x <= CENTET_TILE_X)
			x = CENTET_TILE_X;
		else if (inMap->width - x <= XTILE_COUNT - CENTET_TILE_X)
			x = inMap->width - XTILE_COUNT + CENTET_TILE_X;

	//y����
	if (inMap->height <= YTILE_COUNT)
		y = (inMap->height + 1) / 2.0 - 1;
	//y��������ڿ��ӷ�Χ��
	else
		if (y <= CENTET_TILE_Y)
			y = CENTET_TILE_Y;
		else if ((inMap->height - 1) - y <= YTILE_COUNT - CENTET_TILE_Y)
			y = inMap->height - (YTILE_COUNT - CENTET_TILE_Y + 1);
}