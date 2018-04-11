#pragma once

#include <functional>
#include <SDL2/SDL_main.h>

/*!初始化
 * @note 需要在启动程序前注册好如tile、map等与游戏有关的东西
 * 一旦执行，则游戏就会正式开始
 */
_declspec (dllexport) int run(int argc, char* argv[], const std::function<int()>& initFunc);

//!注册tile
_declspec (dllexport) void registerTile(const char* tileName, const char* fileName);

//!注册map
_declspec (dllexport) void registerMap(const char* fileName);