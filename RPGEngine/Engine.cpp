#include <SDL2/SDL.h>
#include "InitScene.h"
#include "../Engine.h"
#include "SceneManager.h"
#include "MainMenuScene.h"

_declspec (dllexport) int run(int argc, char* argv[], const std::function<int()>& initFunc)
{
	//创建窗口
	const auto window = SDL_CreateWindow(u8"RPG Engine example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 704, SDL_WINDOW_OPENGL);
	const auto renderer = SDL_CreateRenderer(window, -1, 0);
	
	//初始化场景
	auto& sceneManager = SceneManager::getInstance();
	sceneManager.registerScene<InitScene>(renderer);
	sceneManager.switchScene<InitScene>();

	//设置初始化调用
	auto initScene = sceneManager.getSceneObj<InitScene>();
	initScene->addInitStep([&]()
	{
		sceneManager.registerScene<MainMenuScene>(renderer);
		return 0;
	}, u8"初始化场景");
	initScene->addInitStep(initFunc, u8"初始化游戏");
	
	auto shouldCloseWindow = false;

	//进入主循环
	while (!shouldCloseWindow)
	{
		//渲染场景
		SDL_RenderClear(renderer);
		sceneManager.draw(renderer);
		SDL_RenderPresent(renderer);

		//处理事件
		SDL_Event event;

		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				shouldCloseWindow = true;
		}

		//刷新场景
		sceneManager.refresh(0);
	}
	
	SDL_Quit();
	return 0;
}

_declspec (dllexport) void registerTile(const char* fileName)
{
	
}

_declspec (dllexport) void registerMap(const char* fileName)
{
	
}