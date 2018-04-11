#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>
#include "InitScene.h"
#include "../Engine.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "TileTemplate.h"

SDL_Renderer* renderer;

_declspec (dllexport) int run(int argc, char* argv[], const std::function<int()>& initFunc)
{
	//��������
	const auto window = SDL_CreateWindow(u8"RPG Engine example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 704, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	//��ʼ������
	auto& sceneManager = SceneManager::getInstance();
	sceneManager.registerScene<InitScene>(renderer);
	sceneManager.switchScene<InitScene>();

	//���ó�ʼ������
	auto initScene = sceneManager.getSceneObj<InitScene>();
	initScene->addInitStep([&]()
	{
		sceneManager.registerScene<MainMenuScene>(renderer);
		return 0;
	}, u8"��ʼ������");
	initScene->addInitStep(initFunc, u8"��ʼ����Ϸ");
	
	auto shouldCloseWindow = false;

	//������ѭ��
	while (!shouldCloseWindow)
	{
		//��Ⱦ����
		SDL_RenderClear(renderer);
		sceneManager.draw(renderer);
		SDL_RenderPresent(renderer);

		//�����¼�
		SDL_Event event;

		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				shouldCloseWindow = true;
		}

		//ˢ�³���
		sceneManager.refresh(0);
	}
	
	SDL_Quit();
	return 0;
}

_declspec (dllexport) void registerTile(const char* tileName, const char* fileName)
{
	//��ȡ�����ļ�
	std::ifstream file(fileName);
	std::stringstream fileStrStream;
	fileStrStream << file.rdbuf();

	//ע��
	TileTemplate::registerTileTemplate(renderer, tileName, fileStrStream.str());
}

_declspec (dllexport) void registerMap(const char* fileName)
{
	
}