#include <Windows.h>
#include <SDL2/SDL.h>
#include "Resource.h"

SDL_RWops* RE_RWFromResource(const char* resType, const char* resName)
{
	const auto hInst = GetModuleHandleA("RPGEngine.dll");

	const auto hRes = ::FindResourceA(hInst, resName, resType);
	const auto hMem = ::LoadResource(hInst, hRes);
	const auto dwSize = ::SizeofResource(hInst, hRes);
	
	return SDL_RWFromMem(hMem, dwSize);
}