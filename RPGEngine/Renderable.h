#pragma once

struct SDL_Renderer;

class Renderable
{
public:
	//��Ⱦ
	virtual void refresh(double passedTick) = 0;
	//ˢ��
	virtual void draw(SDL_Renderer* renderer) = 0;

	virtual ~Renderable() = default;
};