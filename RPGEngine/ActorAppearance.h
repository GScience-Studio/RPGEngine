#pragma once

#include <map>
#include <memory>
#include <vector>
#include <array>

struct SDL_Renderer;
struct SDL_Texture;

//!actorÕ‚√≤
class ActorAppearance
{
	static std::map<std::string, std::unique_ptr<ActorAppearance>>& getActorAppearanceMap()
	{
		static std::map<std::string, std::unique_ptr<ActorAppearance>> actorAppearanceMap;
		return actorAppearanceMap;
	}

public:
	enum Direction
	{
		FaceFront = 0,
		FaceBack = 1,
		FaceLeft = 2,
		FaceRight = 3
	};
	ActorAppearance(SDL_Renderer* renderer, const std::string& json);

	std::array<std::vector<SDL_Texture*>, 4> actorWalkingImage;

	static void registerActorAppearance(SDL_Renderer* renderer, const char* actorName, const std::string& json)
	{
		getActorAppearanceMap()[actorName] = std::make_unique<ActorAppearance>(renderer, json);
	}

	static ActorAppearance* getActorAppearance(const char* tileName)
	{
		if (!tileName)
			return nullptr;

		return getActorAppearanceMap()[tileName].get();
	}
};
