#pragma once

#include "Renderable.h"
#include "ActorAppearance.h"
#include <string>

class GameMap;

struct Location
{
	GameMap* inMap = nullptr;
	double x = 0, y = 0;
	int level = 0;
};

//!可渲染的actor
class GameActor :public Renderable, public std::enable_shared_from_this<GameActor>
{
	ActorAppearance* mActorAppearance = nullptr;
	
	//!角色方向
	ActorAppearance::Direction mDirection = ActorAppearance::FaceFront;
	//!角色动画帧位置
	unsigned short mAnimationId = 0;
	//!是否播放动画
	bool mIsPlayingAnimation = false;
	//!动画速度（多少秒切换到下一帧）
	double mAnimationSpeed = 0.2;
	//!延迟切换关键帧
	double mWaitedTime = 0.0;

	//!角色位置
	Location mLocation;

	//!角色的渲染使用不同的方式
	void draw(SDL_Renderer*, int, int) override
	{
		throw(std::runtime_error("Couldn't draw an actor by this function"));
	}

public:
	double& x = mLocation.x;
	double& y = mLocation.y;
	int& level = mLocation.level;

	//!角色名称
	const std::string actorName;

	explicit GameActor(const char* actorName) :GameActor(actorName, nullptr) {}
	GameActor(const char* actorName, const char* actorAppearance);

	/*!角色渲染
	 * 为了让角色拥有正确的遮盖等功能，把角色分成了多个部分渲染，
	 * 每个部分最大为一个Tile的大小，越向上z值（用于计算遮盖）越大
	 * part的最大值为ACTOR_HEIGHT / TILE_SIZE
	 */
	void draw(SDL_Renderer* renderer, int xOffset, int yOffset, int part) const;
	void refresh(double passedTick) override;

	//!播放行走动画
	void playAnimation(const ActorAppearance::Direction direction, const double speed)
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
	void turnTo(const ActorAppearance::Direction direction)
	{
		mDirection = direction;
	}

	//!更改actor外观
	void changeApperance(ActorAppearance* renderableActorTemplate)
	{
		mAnimationId = 0;
		mActorAppearance = renderableActorTemplate;
	}

	//!获取外观
	ActorAppearance* getApperance() const
	{
		return mActorAppearance;
	}

	//!获取所在地图
	GameMap* getInMap() const
	{
		return mLocation.inMap;
	}

	//!支持移动到其他地图的移动
	void moveCrossMap(GameMap* map, int x, int y, int level);
};

//!GamePlayer有且只有一个
class GamePlayer :public GameActor
{
	GamePlayer() :GameActor("Player") {}

public:
	static GamePlayer& getGlobalPlayer()
	{
		static std::shared_ptr<GamePlayer> player(new GamePlayer());
		return *player;
	}
};

/*!相机类
 * 所有相机都需要被绑定到actor上以便于自动定位相机位置
 */
class Camera
{
	const GameActor* const mActor;
	Location mLocation;

public:
	explicit Camera(const GameActor* const bindTo) :mActor(bindTo) {}

	//!刷新相机位置
	void refresh();

	//!获取相机所在位置
	const Location& getLocation()
	{
		refresh();
		return mLocation;
	}
};