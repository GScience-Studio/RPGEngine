#pragma once

struct SDL_Renderer;

/*!��������
 * ֧����Ⱦ��ˢ��
 */
class SceneBase
{
public:
	//!��Ⱦ
	virtual void draw(SDL_Renderer* renderer) = 0;
	//!ˢ��
	virtual void refresh(double passedTick) = 0;
	
	explicit SceneBase(SDL_Renderer* renderer) {}
	virtual ~SceneBase() = default;
};