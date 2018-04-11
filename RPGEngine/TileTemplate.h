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

	const TriggerType triggerType = Null;
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