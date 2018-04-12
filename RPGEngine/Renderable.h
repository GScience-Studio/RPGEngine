#pragma once

struct SDL_Renderer;

class Renderable
{
public:
	//��Ⱦ
	virtual void refresh(double passedTick) = 0;
	//ˢ��
	virtual void draw(SDL_Renderer* renderer, int xOffset, int yOffset) = 0;

	virtual ~Renderable() = default;
};