#include "GameActor.h"
#include "../Engine.h"
#include "GameMap.h"
#include <SDL2/SDL.h>

void GameActor::draw(SDL_Renderer* renderer, const int xOffset, const int yOffset, const int part) const
{
	//���û������ò����Ⱦ
	if (!mActorAppearance)
		return;

	//��ȡ��ǰ��ò�µ�ָ��Id������
	const auto texture = mActorAppearance->actorWalkingImage[mDirection][mAnimationId];

	//��ȡ��ǰָ�����ֵ�Ŀ������
	SDL_Rect renderPos;
	renderPos.x = static_cast<int>(xOffset + x * TILE_SIZE);
	renderPos.y = static_cast<int>(yOffset + (y - (part + 1)) * TILE_SIZE);
	renderPos.h = TILE_SIZE;
	renderPos.w = ACTOR_WIDTH;

	//��ȡԴ����
	SDL_Rect sourcePos;
	
	sourcePos.x = 0;
	sourcePos.y = ACTOR_HEIGHT - TILE_SIZE * (part + 1);
	sourcePos.h = TILE_SIZE;
	sourcePos.w = ACTOR_WIDTH;

	//������˲���һ��tile�Ĵ�С����Ⱦ
	if (part == ACTOR_HEIGHT / TILE_SIZE)
	{
		//Ŀ��λ�õĸ߶�Ϊʣ�����������
		renderPos.h = ACTOR_HEIGHT % TILE_SIZE;
		//Ŀ��λ�õ�y���������ƶ�(tile�߶�-�¸�)
		renderPos.y += TILE_SIZE - renderPos.h;
	}

	//������ɫλ�ÿ���һ��tile
	renderPos.y += ACTOR_HEIGHT / TILE_SIZE * TILE_SIZE;

	SDL_RenderCopy(renderer, texture, &sourcePos, &renderPos);
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

	if (mAnimationId >= mActorAppearance->actorWalkingImage[mDirection].size())
		mAnimationId = 0;
}

void Camera::refresh()
{
	mLocation.inMap = mActor->getInMap();
	mLocation.x = mActor->x;
	mLocation.y = mActor->y;

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

void GameActor::moveCrossMap(GameMap* map, const int x, const int y, const int level)
{
	//�ƶ�����ͼ
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