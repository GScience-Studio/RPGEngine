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
#include "ActorAppearance.h"

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

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Register tile from %s", fileName);

	//注册
	TileTemplate::registerTileTemplate(renderer, tileName, fileStrStream.str());
}

_declspec (dllexport) void registerMap(const char* mapName, const char* fileName, GameMapEventProcessorBase* eventProcessor)
{
	//读取完整文件
	std::ifstream file(fileName);
	std::stringstream fileStrStream;
	fileStrStream << file.rdbuf();

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Register map from %s", fileName);

	//注册
	GameMap::registerGameMap(renderer, mapName, fileStrStream.str(), eventProcessor);
}

_declspec (dllexport) void setSpawn(const char* mapName, const int x, const int y, const int level)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Set player spawn point %i %i %i", x, y, level);

	GamePlayer::getGlobalPlayer().moveCrossMap(&GameMap::getGameMap(mapName), x, y, level);
}

//!注册actor
_declspec (dllexport) void registerActorAppearance(const char* actorName, const char* fileName)
{
	//读取完整文件
	std::ifstream file(fileName);
	std::stringstream fileStrStream;
	fileStrStream << file.rdbuf();

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Register actor appearance from %s with name %s", fileName, actorName);

	//注册
	ActorAppearance::registerActorAppearance(renderer, actorName, fileStrStream.str());
}

_declspec (dllexport) void setPlayerAppearance(const char* appearanceName)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Set player appearance to", appearanceName);

	GamePlayer::getGlobalPlayer().changeApperance(ActorAppearance::getActorAppearance(appearanceName));
}