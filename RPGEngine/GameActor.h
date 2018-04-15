#pragma once

#include "Renderable.h"
#include "ActorAppearance.h"

class GameMap;

struct Location
{
	GameMap* inMap = nullptr;
	double x = 0, y = 0;
};

//!����Ⱦ��actor
class GameActor :public Renderable
{
	ActorAppearance* mRenderableActorTemplate = nullptr;
	
	//!��ɫ����
	ActorAppearance::Direction mDirection = ActorAppearance::FaceFront;
	//!��ɫ����֡λ��
	unsigned short mAnimationId = 0;
	//!�Ƿ񲥷Ŷ���
	bool mIsPlayingAnimation = false;
	//!�����ٶȣ��������л�����һ֡��
	double mAnimationSpeed = 0.2;
	//!�ӳ��л��ؼ�֡
	double mWaitedTime = 0.0;

public:
	Location location;

	GameActor() :GameActor(nullptr) {}
	explicit GameActor(ActorAppearance* renderableActorTemplate) :mRenderableActorTemplate(renderableActorTemplate) {}

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;

	//!�������߶���
	void playAnimation(const ActorAppearance::Direction direction, const double speed)
	{
		mDirection = direction;
		mIsPlayingAnimation = true;
		mAnimationSpeed = speed;
	}

	//!ֹͣ���Ŷ���
	void stopAnimation()
	{
		mIsPlayingAnimation = false;
		mAnimationId = 0;
	}

	//!ת��
	void turnTo(const ActorAppearance::Direction direction)
	{
		mDirection = direction;
	}

	//!����actor���
	void changeApperance(ActorAppearance* renderableActorTemplate)
	{
		mRenderableActorTemplate = renderableActorTemplate;
	}

	//!��ȡ���
	ActorAppearance* getApperance() const
	{
		return mRenderableActorTemplate;
	}
};

//!GamePlayer����ֻ��һ��
class GamePlayer :public GameActor
{
	GamePlayer() = default;

public:
	static GamePlayer& getGlobalPlayer()
	{
		static GamePlayer player;
		return player;
	}
};

/*!�����
 * �����������Ҫ���󶨵�actor���Ա����Զ���λ���λ��
 */
class Camera
{
	const GameActor* const mActor;
	Location mLocation;

public:
	explicit Camera(const GameActor* const bindTo) :mActor(bindTo) {}

	//!ˢ�����λ��
	void refresh();

	//!��ȡ�������λ��
	const Location& getLocation()
	{
		refresh();
		return mLocation;
	}
};