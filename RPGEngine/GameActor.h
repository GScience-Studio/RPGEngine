#pragma once

#include "Renderable.h"
#include "RenderableActorTemplate.h"

class GameMap;

struct Location
{
	GameMap* inMap = nullptr;
	double x = 0, y = 0;
};

class GameActor
{
	Location mLocation;

protected:
	explicit GameActor(bool renderable = false) : renderable(renderable) {}

public:
	virtual const Location& getLocation()
	{
		return mLocation;
	}

	const bool renderable;

	double& x = mLocation.x;
	double& y = mLocation.y;
	GameMap*& inMap = mLocation.inMap;

	virtual ~GameActor() = default;
};

//!����Ⱦ��actor
class RenderableGameActor :public GameActor, public Renderable
{
	RenderableActorTemplate* mRenderableActorTemplate = nullptr;
	
	//!��ɫ����
	RenderableActorTemplate::Direction mDirection = RenderableActorTemplate::FaceFront;
	//!��ɫ����֡λ��
	unsigned short mAnimationId = 0;
	//!�Ƿ񲥷Ŷ���
	bool mIsPlayingAnimation = false;
	//!�����ٶȣ��������л�����һ֡��
	double mAnimationSpeed = 0.2;
	//!�ӳ��л��ؼ�֡
	double mWaitedTime = 0.0;

public:
	RenderableGameActor() :RenderableGameActor(nullptr) {}
	explicit RenderableGameActor(RenderableActorTemplate* renderableActorTemplate) :GameActor(true), mRenderableActorTemplate(renderableActorTemplate) {}

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;

	//!�������߶���
	void playAnimation(const RenderableActorTemplate::Direction direction, const double speed)
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
	void turnTo(const RenderableActorTemplate::Direction direction)
	{
		mDirection = direction;
	}

	//!����actor���
	void changeApperance(RenderableActorTemplate* renderableActorTemplate)
	{
		mRenderableActorTemplate = renderableActorTemplate;
	}

	//!��ȡ���
	RenderableActorTemplate* getApperance() const
	{
		return mRenderableActorTemplate;
	}
};

class GamePlayer :public RenderableGameActor
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
class Camera :GameActor
{
	const GameActor* mActor;

public:
	 explicit Camera(const GameActor* bindTo) :mActor(bindTo) {}

	//!ˢ�����λ��
	void refresh();

	//!��ȡ�������λ��
	const Location& getLocation() override
	{
		refresh();
		return GameActor::getLocation();
	}
};