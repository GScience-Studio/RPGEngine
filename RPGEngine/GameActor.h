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

//!����Ⱦ��actor
class GameActor :public Renderable, public std::enable_shared_from_this<GameActor>
{
	ActorAppearance* mActorAppearance = nullptr;
	
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

	//!��ɫλ��
	Location mLocation;

	//!��ɫ����Ⱦʹ�ò�ͬ�ķ�ʽ
	void draw(SDL_Renderer*, int, int) override
	{
		throw(std::runtime_error("Couldn't draw an actor by this function"));
	}

public:
	double& x = mLocation.x;
	double& y = mLocation.y;
	int& level = mLocation.level;

	//!��ɫ����
	const std::string actorName;

	explicit GameActor(const char* actorName) :GameActor(actorName, nullptr) {}
	GameActor(const char* actorName, const char* actorAppearance);

	/*!��ɫ��Ⱦ
	 * Ϊ���ý�ɫӵ����ȷ���ڸǵȹ��ܣ��ѽ�ɫ�ֳ��˶��������Ⱦ��
	 * ÿ���������Ϊһ��Tile�Ĵ�С��Խ����zֵ�����ڼ����ڸǣ�Խ��
	 * part�����ֵΪACTOR_HEIGHT / TILE_SIZE
	 */
	void draw(SDL_Renderer* renderer, int xOffset, int yOffset, int part) const;
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
		mAnimationId = 0;
		mActorAppearance = renderableActorTemplate;
	}

	//!��ȡ���
	ActorAppearance* getApperance() const
	{
		return mActorAppearance;
	}

	//!��ȡ���ڵ�ͼ
	GameMap* getInMap() const
	{
		return mLocation.inMap;
	}

	//!֧���ƶ���������ͼ���ƶ�
	void moveCrossMap(GameMap* map, int x, int y, int level);
};

//!GamePlayer����ֻ��һ��
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