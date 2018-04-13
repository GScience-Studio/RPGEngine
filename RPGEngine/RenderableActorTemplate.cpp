#include "RenderableActorTemplate.h"
#include <SDL2/SDL_image.h>
#include <json/json.h>

RenderableActorTemplate::RenderableActorTemplate(SDL_Renderer* renderer, const std::string& json)
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
				actorWalkingImage[direction][i] = IMG_LoadTexture(renderer, jsonData[i].asCString());
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