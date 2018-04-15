#include "GameAction.h"
#include <iostream>

bool ActorLinearMoveAction::isFinish()
{
	return mTime <= 0;
}

void ActorLinearMoveAction::refresh(const double passedTick)
{
	switch (mDirection)
	{
	case RenderableActorTemplate::FaceFront:
		if ((mTime -= passedTick) <= 0)
			mActor->location.y = mTo;
		else
			mActor->location.y += mSpeed * passedTick;
		break;
	case RenderableActorTemplate::FaceBack:
		if ((mTime -= passedTick) <= 0)
			mActor->location.y = mTo;
		else
			mActor->location.y -= mSpeed * passedTick;
		break;
	case RenderableActorTemplate::FaceRight:
		if ((mTime -= passedTick) <= 0)
			mActor->location.x = mTo;
		else
			mActor->location.x += mSpeed * passedTick;
		break;
	case RenderableActorTemplate::FaceLeft:
		if ((mTime -= passedTick) <= 0)
			mActor->location.x = mTo;
		else
			mActor->location.x -= mSpeed * passedTick;
		break;
	}

	if (isFinish())
		mActor->stopAnimation();
}

ActorLinearMoveAction::ActorLinearMoveAction(GameActor* actor, const RenderableActorTemplate::Direction direction, const int distance, const double time)
	:mTime(time), mDirection(direction), mActor(actor),
	mSpeed(distance / time)
{
	//处理动画
	const auto animationSpeed = time / (distance * actor->getApperance()->actorWalkingImage[RenderableActorTemplate::FaceRight].size());
	actor->playAnimation(direction, animationSpeed);

	//计算目标位置
	switch (mDirection)
	{
	case RenderableActorTemplate::FaceFront:
		mTo = mActor->location.y + distance;
		break;
	case RenderableActorTemplate::FaceBack:
		mTo = mActor->location.y - distance;
		break;
	case RenderableActorTemplate::FaceRight:
		mTo = mActor->location.x + distance;
		break;
	case RenderableActorTemplate::FaceLeft:
		mTo = mActor->location.x - distance;
		break;
	}
}