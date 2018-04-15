#include "GameActor.h"
#include "../Engine.h"
#include "GameMap.h"
#include <SDL2/SDL.h>

void GameActor::draw(SDL_Renderer* renderer, const int xOffset, const int yOffset, const int part) const
{
	//如果没设置外貌则不渲染
	if (!mActorAppearance)
		return;

	//获取当前外貌下的指定Id的纹理
	const auto texture = mActorAppearance->actorWalkingImage[mDirection][mAnimationId];

	//获取当前指定部分的目标坐标
	SDL_Rect renderPos;
	renderPos.x = static_cast<int>(xOffset + x * TILE_SIZE);
	renderPos.y = static_cast<int>(yOffset + (y - (part + 1)) * TILE_SIZE);
	renderPos.h = TILE_SIZE;
	renderPos.w = ACTOR_WIDTH;

	//获取源坐标
	SDL_Rect sourcePos;
	
	sourcePos.x = 0;
	sourcePos.y = ACTOR_HEIGHT - TILE_SIZE * (part + 1);
	sourcePos.h = TILE_SIZE;
	sourcePos.w = ACTOR_WIDTH;

	//修正最顶端不到一个tile的大小的渲染
	if (part == ACTOR_HEIGHT / TILE_SIZE)
	{
		//目标位置的高度为剩余的像素数量
		renderPos.h = ACTOR_HEIGHT % TILE_SIZE;
		//目标位置的y坐标向下移动(tile高度-新高)
		renderPos.y += TILE_SIZE - renderPos.h;
	}

	SDL_RenderCopy(renderer, texture, &sourcePos, &renderPos);
}

void GameActor::refresh(const double passedTick)
{
	//判断是否需要处理动画
	if (!mIsPlayingAnimation && mAnimationId == 0)
		return;

	//判断是否到达延迟
	if ((mWaitedTime += passedTick) < mAnimationSpeed)
		return;

	mWaitedTime -= mAnimationSpeed;
	++mAnimationId;

	if (mAnimationId >= mActorAppearance->actorWalkingImage[mDirection].size())
		mAnimationId = 0;
}

void Camera::refresh()
{
	mLocation.inMap = mActor->getInMap();
	mLocation.x = mActor->x;
	mLocation.y = mActor->y;

	//尽量多显示地图处理

	//x居中
	if (mLocation.inMap->width <= XTILE_COUNT)
		mLocation.x = (mLocation.inMap->width + 1) / 2.0 - 1;
	//x限制相机在可视范围内
	else
		if (mLocation.x <= CENTET_TILE_X)
			mLocation.x = CENTET_TILE_X;
		else if (mLocation.inMap->width - mLocation.x <= XTILE_COUNT - CENTET_TILE_X)
			mLocation.x = mLocation.inMap->width - XTILE_COUNT + CENTET_TILE_X;

	//y居中
	if (mLocation.inMap->height <= YTILE_COUNT)
		mLocation.y = (mLocation.inMap->height + 1) / 2.0 - 1;
	//y限制相机在可视范围内
	else
		if (mLocation.y <= CENTET_TILE_Y)
			mLocation.y = CENTET_TILE_Y;
		else if ((mLocation.inMap->height - 1) - mLocation.y <= YTILE_COUNT - CENTET_TILE_Y)
			mLocation.y = mLocation.inMap->height - (YTILE_COUNT - CENTET_TILE_Y + 1);
}

void GameActor::moveCrossMap(GameMap* map, const int x, const int y, const int level)
{
	//移动到地图
	if (map != mLocation.inMap)
	{
		if (mLocation.inMap)
			mLocation.inMap->actorList.erase(actorName);

		mLocation.inMap = map;

		if (mLocation.inMap)
			mLocation.inMap->actorList[actorName] = shared_from_this();
	}
	
	mLocation.x = x;
	mLocation.y = y;
	mLocation.level = level;
}

GameActor::GameActor(const char* actorName, const char* actorAppearance) :
	mActorAppearance(ActorAppearance::getActorAppearance(actorAppearance)),
	actorName(actorName)
{}