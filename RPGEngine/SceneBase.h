#pragma once

#include "Renderable.h"

/*!场景基类
 * 支持渲染和刷新
 */
class SceneBase :public Renderable
{
public:
	explicit SceneBase(SDL_Renderer* renderer) {}
};