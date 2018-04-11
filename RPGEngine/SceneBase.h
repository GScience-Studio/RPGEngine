#pragma once

struct SDL_Renderer;

/*!场景基类
 * 支持渲染和刷新
 */
class SceneBase
{
public:
	//!渲染
	virtual void draw(SDL_Renderer* renderer) = 0;
	//!刷新
	virtual void refresh(double passedTick) = 0;
	
	explicit SceneBase(SDL_Renderer* renderer) {}
	virtual ~SceneBase() = default;
};