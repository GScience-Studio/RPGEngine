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

		//读取image和trigger
		const int tileImageCount = root["image_list"].size();

		tileImageList.resize(tileImageCount);
		tileAnimationTriggerList.resize(tileImageCount);

		//有Action
		if (!root["action"].empty())
		{
			if (root["action"].asString() == "air")
				tileAction = Air;
			else if (root["action"].asString() == "barrier")
				tileAction = Barrier;
			else
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Acton should be \"air\" \"barrier\"");
		}
		else
			tileAction = Air;

		//image信息
		for (auto i = 0; i < tileImageCount; i++)
		{
			auto timeImageInfo = root["image_list"][i];

			//图片
			tileImageList[i] = IMG_LoadTexture(renderer, timeImageInfo["image"].asCString());

			//有触发器
			if (!timeImageInfo["trigger"].empty())
			{

				const auto triggerType = timeImageInfo["trigger"]["type"].asString();

				if (triggerType == "delay")
					tileAnimationTriggerList[i] = std::make_unique<TriggerDelay>(timeImageInfo["trigger"]["delay"].asDouble());
				else
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, u8"Trigger type should be \"delay\"");
			}
		}
	}
	catch (std::exception& e)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed do read tile json because %s", e.what());

		return;
	}
}