#pragma once

#include "GameActor.h"

class GameAction
{
public:
	virtual bool isFinish() = 0;
	virtual void refresh(double passedTick) = 0;

	virtual ~GameAction() = default;
};

class ActorLinearMoveAction :public GameAction
{
	double mTime = 0;
	double mTo = 0;
	const RenderableActorTemplate::Direction mDirection;
	GameActor* mActor;
	const double mSpeed;

public:
	/*!ֱ���ƶ���ң�distanceΪtile��
	 * @param direction �ƶ��ķ���
	 * @param actor �ƶ���Actor
	 * @param distance �ƶ��ľ���
	 * @param time �ƶ���ʱ�� 
	 */
	ActorLinearMoveAction(GameActor* actor, RenderableActorTemplate::Direction direction, int distance, double time);

	bool isFinish() override;
	void refresh(double passedTick) override;
};