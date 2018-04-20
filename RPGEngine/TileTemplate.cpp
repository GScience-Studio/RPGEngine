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

		//��ȡimage��trigger
		const int tileImageCount = root["image_list"].size();

		tileImageList.resize(tileImageCount);
		tileAnimationTriggerList.resize(tileImageCount);

		for (auto i = 0; i < tileImageCount; i++)
		{
			auto timeImageInfo = root["image_list"][i];

			//ͼƬ
			tileImageList[i] = IMG_LoadTexture(renderer, timeImageInfo["image"].asCString());
			
			//û�д�����
			if (timeImageInfo["trigger"].empty())
				continue;

			//�д�����
			const auto triggerType = timeImageInfo["trigger"]["type"].asString();

			if (triggerType == "delay")
				tileAnimationTriggerList[i] = std::make_unique<TriggerDelay>(timeImageInfo["trigger"]["delay"].asDouble());
			else
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Trigger type should be \"delay\"");
		}
	}
	catch (std::exception& e)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed do read tile json because %s", e.what());

		return;
	}
}