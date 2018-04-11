#pragma once

#include <functional>
#include <vector>
#include <string>
#include "SceneBase.h"

struct SDL_Texture;

class InitScene : public SceneBase
{
	//!全屏Logo
	SDL_Texture* mFullSceneLogo;

	//!初始化流程
	std::vector<std::pair<std::function<int()>, std::string>> mInitFunctionGroup;

public:
	explicit InitScene(SDL_Renderer* renderer);

	//!增加初始化过程
	void addInitStep(const std::function<int()>& func, const std::string& stepName)
	{
		mInitFunctionGroup.emplace_back(std::make_pair(func, stepName));
	}

	void draw(SDL_Renderer* renderer) override;
	void refresh(double passedTick) override;
};