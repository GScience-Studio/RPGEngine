#pragma once

#include <map>
#include <memory>
#include <vector>
#include <array>

struct SDL_Renderer;
struct SDL_Texture;

class RenderableActorTemplate
{
	static std::map<std::string, std::unique_ptr<RenderableActorTemplate>>& getActorTemplateMap()
	{
		static std::map<std::string, std::unique_ptr<RenderableActorTemplate>> actorTemplateMap;
		return actorTemplateMap;
	}

public:
	enum Direction
	{
		FaceFront = 0,
		FaceBack = 1,
		FaceLeft = 2,
		FaceRight = 3
	};
	RenderableActorTemplate(SDL_Renderer* renderer, const std::string& json);

	std::array<std::vector<SDL_Texture*>, 4> actorWalkingImage;

	static void registerActorTemplate(SDL_Renderer* renderer, const char* actorName, const std::string& json)
	{
		getActorTemplateMap()[actorName] = std::make_unique<RenderableActorTemplate>(renderer, json);
	}

	static RenderableActorTemplate& getActorTemplate(const char* tileName)
	{
		return *getActorTemplateMap()[tileName];
	}
};
