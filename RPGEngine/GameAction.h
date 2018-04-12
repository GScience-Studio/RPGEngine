#pragma once

#include "GameActor.h"

class GameAction
{
public:
	virtual bool isFinish() = 0;
	virtual void refresh(double passedTick) = 0;

	virtual ~GameAction() = default;
};

class ActorMoveAction :public GameAction
{
	double mTime = 0;

	const double mToX;
	const double mToY;

	GameActor* mActor;

	const double mSpeedX;
	const double mSpeedY;

public:
	ActorMoveAction(GameActor* actor, double toX, double toY, double time);

	bool isFinish() override;
	void refresh(double passedTick) override;
};