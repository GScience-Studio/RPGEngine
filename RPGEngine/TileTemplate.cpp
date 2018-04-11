#include "TileTemplate.h"
#include <SDL2/SDL_image.h>
#include <json/json.h>

TileTemplate::TileTemplate(SDL_Renderer* renderer, const std::string& json)
{
	try
	{
		Json::CharReaderBuilder readerBuilder;
		auto reader = readerBuilder.newCharReader();
		Json::Value root;

		reader->parse(&json.front(), &json.back(), &root, nullptr);

		const int tileImageCount = root["image_list"].size();

		tileImageList.resize(tileImageCount);
		tileAnimationTriggerList.resize(tileImageCount);

		for (auto i = 0; i < tileImageCount; i++)
		{
			tileImageList[i] = IMG_LoadTexture(renderer, root["image_list"][i]["image"].asCString());
		}
	}
	catch (std::exception e)
	{
		return;
	}
}