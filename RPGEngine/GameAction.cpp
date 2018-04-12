#include "GameAction.h"
#include "../Engine.h"
#include <iostream>

bool ActorMoveAction::isFinish()
{
	return mTime <= 0;
}

void ActorMoveAction::refresh(double passedTick)
{
	if (!isFinish())
	{
		mTime -= passedTick;
		mActor->x += mSpeedX * passedTick;
		mActor->y += mSpeedY * passedTick;
	}
	if (isFinish())
	{
		mActor->x = mToX;
		mActor->y = mToY;
	}
}

ActorMoveAction::ActorMoveAction(GameActor* actor, const double toX, const double toY, const double time)
	:mTime(time), mToX(static_cast<int>(toX)), mToY(static_cast<int>(toY)), mActor(actor),
	mSpeedX((toX - actor->x) / time),
	mSpeedY((toY - actor->y) / time)
{
	
}