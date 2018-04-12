#pragma once

#include <functional>
#include <vector>
#include <string>
#include "SceneBase.h"

struct SDL_Texture;

class InitScene : public SceneBase
{
	//!ȫ��Logo
	SDL_Texture* mFullSceneLogo;

	//!��ʼ������
	std::vector<std::pair<std::function<int()>, std::string>> mInitFunctionGroup;

public:
	explicit InitScene(SDL_Renderer* renderer);

	//!���ӳ�ʼ������
	void addInitStep(const std::function<int()>& func, const std::string& stepName)
	{
		mInitFunctionGroup.emplace_back(std::make_pair(func, stepName));
	}

	void draw(SDL_Renderer* renderer, int xOffset, int yOffset) override;
	void refresh(double passedTick) override;
};