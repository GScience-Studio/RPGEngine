#pragma once

#include <map>
#include <memory>
#include "SceneBase.h"

using SceneKey = size_t;

class SceneManager
{
	std::map<SceneKey, std::shared_ptr<SceneBase>> mSceneMap;
	
	std::shared_ptr<SceneBase> mShownScene = nullptr;
	std::shared_ptr<SceneBase> mNextScene = nullptr;

	SceneManager() = default;

public:
	void operator =(const SceneManager&) = delete;
	void operator =(const SceneManager&&) = delete;

	template<class scene, class ...t> void registerScene(t... args)
	{
		mSceneMap[typeid(scene).hash_code()] = std::make_shared<scene>(args...);
	}

	template<class scene> void switchScene()
	{
		//显示了场景则需要等到事件全部完成后切换
		if (!mShownScene)
			mShownScene = getSceneObj<scene>();
		else
			mNextScene = getSceneObj<scene>();
	}

	template<class scene> std::shared_ptr<scene> getSceneObj() const
	{
		auto findResult = mSceneMap.find(typeid(scene).hash_code());

		if (findResult == mSceneMap.end())
			return nullptr;

		return std::static_pointer_cast<scene>(findResult->second);
	}

	void draw(SDL_Renderer* renderer) const
	{
		//渲染
		mShownScene->draw(renderer, 0, 0);
	}

	void refresh(const double passedTick)
	{
		//刷新
		mShownScene->refresh(passedTick);

		//切换场景
		if (mNextScene)
		{
			mShownScene = mNextScene;
			mNextScene = nullptr;
		}
	}

	static SceneManager& getInstance()
	{
		static SceneManager sceneManager;
		return sceneManager;
	}
};
