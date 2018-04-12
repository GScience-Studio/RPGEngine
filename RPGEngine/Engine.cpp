#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>
#include "InitScene.h"
#include "../Engine.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "TileTemplate.h"
#include "GameMap.h"
#include "GameScene.h"
#include "GameActor.h"

SDL_Renderer* renderer;

_declspec (dllexport) int run(int argc, char* argv[], const std::function<int()>& initFunc)
{
	//创建窗口
	const auto window = SDL_CreateWindow(u8"RPG Engine example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	//初始化场景
	auto& sceneManager = SceneManager::getInstance();
	sceneManager.registerScene<InitScene>(renderer);
	sceneManager.registerScene<GameScene>(renderer);
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

	auto lastTick = SDL_GetTicks() / 1000.0;

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
		const auto nowTick = SDL_GetTicks() / 1000.0;
		sceneManager.refresh(nowTick - lastTick);
		lastTick = nowTick;
	}
	
	SDL_Quit();
	return 0;
}

_declspec (dllexport) void registerTile(const char* tileName, const char* fileName)
{
	//读取完整文件
	std::ifstream file(fileName);
	std::stringstream fileStrStream;
	fileStrStream << file.rdbuf();

	//注册
	TileTemplate::registerTileTemplate(renderer, tileName, fileStrStream.str());
}

_declspec (dllexport) void registerMap(const char* mapName, const char* fileName, GameMapEventProcessorBase* eventProcessor)
{
	//读取完整文件
	std::ifstream file(fileName);
	std::stringstream fileStrStream;
	fileStrStream << file.rdbuf();

	//注册
	GameMap::registerGameMap(renderer, mapName, fileStrStream.str(), eventProcessor);
}

_declspec (dllexport) void setSpawn(const char* mapName, const int x, const int y)
{
	GamePlayer::getGlobalPlayer().inMap = &GameMap::getGameMap(mapName);
	GamePlayer::getGlobalPlayer().x = x;
	GamePlayer::getGlobalPlayer().y = y;
}