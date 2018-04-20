#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>

struct SDL_Texture;
struct SDL_Renderer;

//!tile����������
class TileAnimationTrigger
{
public:
	enum TriggerType
	{
		Null, Delay, WhenActorMoveIn, WhenActorMoveOut
	};

protected:
	explicit TileAnimationTrigger(const TriggerType triggerType) :triggerType(triggerType) {}

public:
	//!��ֹ�򵥵ĸ���
	TileAnimationTrigger& operator =(const TileAnimationTrigger& trigger) = delete;

	//!����ʵ��
	virtual std::shared_ptr<TileAnimationTrigger> createCopy() const = 0;

	const TriggerType triggerType = Null;
	std::shared_ptr<void> triggerData = nullptr;

	virtual ~TileAnimationTrigger() = default;
};

//!�ӳٴ�����
class TriggerDelay :public TileAnimationTrigger
{
public:
	//!��ȡ�ӳٵ�ʱ��
	double getDelayTime() const
	{
		return *std::static_pointer_cast<double>(triggerData);
	}

	//!�����ӳ�ʱ��
	void setDelayTime(const double delayTime) const
	{
		*std::static_pointer_cast<double>(triggerData) = delayTime;
	}

	//!�ӳٵ�ʱ��
	explicit TriggerDelay(const double delayTime) :TileAnimationTrigger(Delay)
	{
		triggerData = std::make_shared<double>(delayTime);
	}

	//!��������
	std::shared_ptr<TileAnimationTrigger> createCopy() const override
	{
		return std::make_shared<TriggerDelay>(getDelayTime());
	}
};

/*!tileģ��
 * ��������GameTile
 */
class TileTemplate
{
	static std::map<std::string, std::unique_ptr<TileTemplate>>& getTileTemplateMap()
	{
		static std::map<std::string, std::unique_ptr<TileTemplate>> tileTemplateMap;
		return tileTemplateMap;
	}

public:
	TileTemplate(SDL_Renderer* renderer, const std::string& json);

	std::vector<SDL_Texture*> tileImageList;
	std::vector<std::unique_ptr<TileAnimationTrigger>> tileAnimationTriggerList;

	static void registerTileTemplate(SDL_Renderer* renderer, const char* tileName, const std::string& json)
	{
		getTileTemplateMap()[tileName] = std::make_unique<TileTemplate>(renderer, json);
	}

	static TileTemplate& getTileTemplate(const char* tileName)
	{
		return *getTileTemplateMap()[tileName];
	}
};