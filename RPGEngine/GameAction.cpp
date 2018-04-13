#include "GameAction.h"
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

		if (mActor->renderable)
		{
			auto renderableActor = static_cast<RenderableGameActor*>(mActor);
			renderableActor->stopAnimation();
		}
	}
}

ActorMoveAction::ActorMoveAction(GameActor* actor, const double toX, const double toY, const double time)
	:mTime(time), mToX(static_cast<int>(toX)), mToY(static_cast<int>(toY)), mActor(actor),
	mSpeedX((toX - actor->x) / time),
	mSpeedY((toY - actor->y) / time)
{
	//是否处理动画
	if (mActor->renderable)
	{
		auto renderableActor = static_cast<RenderableGameActor*>(actor);
		
		double animationSpeed = 0;

		if (mSpeedX != 0)
			animationSpeed = time / (abs(toX - actor->x) * renderableActor->getApperance()->actorWalkingImage[RenderableActorTemplate::FaceRight].size());
		else if (mSpeedY != 0)
			animationSpeed = time / (abs(toY - actor->y) * renderableActor->getApperance()->actorWalkingImage[RenderableActorTemplate::FaceRight].size());
		
		if (mSpeedX > 0)
			renderableActor->playAnimation(RenderableActorTemplate::FaceRight, animationSpeed);
		else if (mSpeedX < 0)
			renderableActor->playAnimation(RenderableActorTemplate::FaceLeft, animationSpeed);
		else if (mSpeedY > 0)
			renderableActor->playAnimation(RenderableActorTemplate::FaceFront, animationSpeed);
		else if (mSpeedY < 0)
			renderableActor->playAnimation(RenderableActorTemplate::FaceBack, animationSpeed);

	}
}