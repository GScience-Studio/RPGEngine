#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ReadFromResource.h"
#include "InitScene.h"
#include "SceneManager.h"
#include "MainMenuScene.h"

void InitScene::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, mFullSceneLogo, nullptr, nullptr);
}

void InitScene::refresh(double passedTick)
{
	if (mInitFunctionGroup.empty())
		SceneManager::getInstance().switchScene<MainMenuScene>();
	else
	{
		const auto initStep = mInitFunctionGroup.begin();
		const auto stepName = initStep->second;
		const auto result = initStep->first();
		mInitFunctionGroup.erase(mInitFunctionGroup.begin());
	}
}

InitScene::InitScene(SDL_Renderer* renderer) :SceneBase(renderer)
{
	mFullSceneLogo = IMG_LoadTexture_RW(renderer, RE_RWFromResource("PNG", "FULL_SCENE_LOGO"), true);
}