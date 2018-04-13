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

//!可渲染的actor
class RenderableGameActor :public GameActor, public Renderable
{
	RenderableActorTemplate* mRenderableActorTemplate = nullptr;
	
	//!角色方向
	RenderableActorTemplate::Direction mDirection = RenderableActorTemplate::FaceFront;
	//!角色动画帧位置
	unsigned short mAnimationId = 0;
	//!是否播放动画
	bool mIsPlayingAnimation = false;
	//!动画速度（多少秒切换到下一帧）
	double mAnimationSpeed = 0.2;
	//!延迟切换关键帧
	double mWaitedTime = 0.0;

public:
	RenderableGameActor() :RenderableGameActor(nullptr) {}
	explicit RenderableGameActor(RenderableActorTemplate* renderableActorTemplate) :GameActor(true), mRenderableActorTemplate(renderableActorTemplate) {}

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;

	//!播放行走动画
	void playAnimation(const RenderableActorTemplate::Direction direction, const double speed)
	{
		mDirection = direction;
		mIsPlayingAnimation = true;
		mAnimationSpeed = speed;
	}

	//!停止播放动画
	void stopAnimation()
	{
		mIsPlayingAnimation = false;
		mAnimationId = 0;
	}

	//!转向
	void turnTo(const RenderableActorTemplate::Direction direction)
	{
		mDirection = direction;
	}

	//!更改actor外观
	void changeApperance(RenderableActorTemplate* renderableActorTemplate)
	{
		mRenderableActorTemplate = renderableActorTemplate;
	}

	//!获取外观
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

/*!相机类
 * 所有相机都需要被绑定到actor上以便于自动定位相机位置
 */
class Camera :GameActor
{
	const GameActor* mActor;

public:
	 explicit Camera(const GameActor* bindTo) :mActor(bindTo) {}

	//!刷新相机位置
	void refresh();

	//!获取相机所在位置
	const Location& getLocation() override
	{
		refresh();
		return GameActor::getLocation();
	}
};