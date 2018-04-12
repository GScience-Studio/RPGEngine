#pragma once

struct SDL_Renderer;

class Renderable
{
public:
	//äÖÈ¾
	virtual void refresh(double passedTick) = 0;
	//Ë¢ĞÂ
	virtual void draw(SDL_Renderer* renderer, int xOffset, int yOffset) = 0;

	virtual ~Renderable() = default;
};