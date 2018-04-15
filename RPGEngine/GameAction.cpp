#include "GameAction.h"

bool ActorLinearMoveAction::isFinish()
{
	return mTime <= 0;
}

void ActorLinearMoveAction::refresh(const double passedTick)
{
	switch (mDirection)
	{
	case ActorAppearance::FaceFront:
		if ((mTime -= passedTick) <= 0)
			mActor->y = mTo;
		else
			mActor->y += mSpeed * passedTick;
		break;
	case ActorAppearance::FaceBack:
		if ((mTime -= passedTick) <= 0)
			mActor->y = mTo;
		else
			mActor->y -= mSpeed * passedTick;
		break;
	case ActorAppearance::FaceRight:
		if ((mTime -= passedTick) <= 0)
			mActor->x = mTo;
		else
			mActor->x += mSpeed * passedTick;
		break;
	case ActorAppearance::FaceLeft:
		if ((mTime -= passedTick) <= 0)
			mActor->x = mTo;
		else
			mActor->x -= mSpeed * passedTick;
		break;
	}

	if (isFinish())
		mActor->stopAnimation();
}

ActorLinearMoveAction::ActorLinearMoveAction(GameActor* actor, const ActorAppearance::Direction direction, const int distance, const double time)
	:mTime(time), mDirection(direction), mActor(actor),
	mSpeed(distance / time)
{
	//处理动画
	const auto animationSpeed = time / (distance * actor->getApperance()->actorWalkingImage[ActorAppearance::FaceRight].size());
	actor->playAnimation(direction, animationSpeed);

	//计算目标位置
	switch (mDirection)
	{
	case ActorAppearance::FaceFront:
		mTo = mActor->y + distance;
		break;
	case ActorAppearance::FaceBack:
		mTo = mActor->y - distance;
		break;
	case ActorAppearance::FaceRight:
		mTo = mActor->x + distance;
		break;
	case ActorAppearance::FaceLeft:
		mTo = mActor->x - distance;
		break;
	}
}