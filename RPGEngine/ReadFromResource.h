#pragma once

struct SDL_RWops;

SDL_RWops* RE_RWFromResource(const char* resType, const char* resName);
