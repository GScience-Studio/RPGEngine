#include "ActorAppearance.h"
#include <SDL2/SDL_image.h>
#include <json/json.h>
#include "../Engine.h"

ActorAppearance::ActorAppearance(SDL_Renderer* renderer, const std::string& json)
{
	try
	{
		Json::CharReaderBuilder readerBuilder;
		auto reader = readerBuilder.newCharReader();
		Json::Value root;

		reader->parse(&json.front(), &json.back(), &root, nullptr);

		const auto loadFacingImage = [&](const char* jsonKey, Direction direction)
		{
			auto jsonData = root[jsonKey];
			const int imageCount = jsonData.size();
			actorWalkingImage[direction].resize(imageCount);

			for (auto i = 0; i < imageCount; ++i)
			{
				auto surface = IMG_Load(jsonData[i].asCString());
				
				//如果和设定不符修改大小
				if (surface->w != ACTOR_WIDTH || surface->h != ACTOR_HEIGHT)
				{
					auto newSurface = SDL_CreateRGBSurfaceWithFormat(0, ACTOR_WIDTH, ACTOR_HEIGHT, 32, surface->format->format);
					SDL_BlitScaled(surface, nullptr, newSurface, nullptr);
					SDL_FreeSurface(surface);
					surface = newSurface;
				}
				actorWalkingImage[direction][i] = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);
			}
		};

		loadFacingImage("face_front", FaceFront);
		loadFacingImage("face_back", FaceBack);
		loadFacingImage("face_left", FaceLeft);
		loadFacingImage("face_right", FaceRight);
	}
	catch (std::exception&)
	{
		return;
	}
}
