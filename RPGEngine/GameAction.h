#pragma once

#include "GameActor.h"

class GameAction
{
public:
	virtual bool isFinish() = 0;
	virtual void refresh(double passedTick) = 0;

	virtual ~GameAction() = default;
};

//!直线移动玩家
class ActorLinearMoveAction :public GameAction
{
	double mTime = 0;
	double mTo = 0;
	const ActorAppearance::Direction mDirection;
	GameActor* mActor;
	const double mSpeed;

public:
	/*!直线移动玩家，distance为tile数
	 * @param direction 移动的方向
	 * @param actor 移动的Actor
	 * @param distance 移动的距离
	 * @param time 移动的时间 
	 */
	ActorLinearMoveAction(GameActor* actor, ActorAppearance::Direction direction, int distance, double time);

	bool isFinish() override;
	void refresh(double passedTick) override;
};