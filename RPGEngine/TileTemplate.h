#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>

struct SDL_Texture;
struct SDL_Renderer;

//!tile动画触发器
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
	//!禁止简单的复制
	TileAnimationTrigger& operator =(const TileAnimationTrigger& trigger) = delete;

	//!复制实例
	virtual std::shared_ptr<TileAnimationTrigger> createCopy() const = 0;

	const TriggerType triggerType = Null;
	std::shared_ptr<void> triggerData = nullptr;

	virtual ~TileAnimationTrigger() = default;
};

//!延迟触发器
class TriggerDelay :public TileAnimationTrigger
{
public:
	//!获取延迟的时间
	double getDelayTime() const
	{
		return *std::static_pointer_cast<double>(triggerData);
	}

	//!设置延迟时间
	void setDelayTime(const double delayTime) const
	{
		*std::static_pointer_cast<double>(triggerData) = delayTime;
	}

	//!延迟的时间
	explicit TriggerDelay(const double delayTime) :TileAnimationTrigger(Delay)
	{
		triggerData = std::make_shared<double>(delayTime);
	}

	//!创建拷贝
	std::shared_ptr<TileAnimationTrigger> createCopy() const override
	{
		return std::make_shared<TriggerDelay>(getDelayTime());
	}
};

/*!tile模板
 * 用来创建GameTile
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