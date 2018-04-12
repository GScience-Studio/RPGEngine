#pragma once

#include <functional>
#include <SDL2/SDL_main.h>

#define TILE_SIZE 64

#define XTILE_COUNT 16
#define YTILE_COUNT 12

#define WINDOW_WIDTH (TILE_SIZE * XTILE_COUNT)
#define WINDOW_HEIGHT (TILE_SIZE * YTILE_COUNT)

class GameMapEventProcessorBase;

/*!初始化
 * @note 需要在启动程序前注册好如tile、map等与游戏有关的东西
 * 一旦执行，则游戏就会正式开始
 */
_declspec (dllexport) int run(int argc, char* argv[], const std::function<int()>& initFunc);

//!注册tile
_declspec (dllexport) void registerTile(const char* tileName, const char* fileName);

//!注册map
_declspec (dllexport) void registerMap(const char* mapName, const char* fileName, GameMapEventProcessorBase* eventProcessor);

//!设置开始游戏时的位置
_declspec (dllexport) void setSpawn(const char* mapName, int x, int y);