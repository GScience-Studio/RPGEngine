#pragma once

#include <functional>
#include <SDL2/SDL_main.h>

#define TILE_SIZE static_cast<int>(64)

#define ACTOR_HEIGHT static_cast<int>(96)
#define ACTOR_WIDTH TILE_SIZE

#define XTILE_COUNT static_cast<int>(17)
#define YTILE_COUNT static_cast<int>(13)

#define WINDOW_WIDTH (TILE_SIZE * XTILE_COUNT)
#define WINDOW_HEIGHT (TILE_SIZE * YTILE_COUNT)

#define CENTET_TILE_X ((XTILE_COUNT + 1) / 2.0 - 1)
#define CENTET_TILE_Y ((YTILE_COUNT + 1) / 2.0 - 1)

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

//!注册actor
_declspec (dllexport) void registerActor(const char* actorName, const char* fileName);

//!设置开始游戏时的位置
_declspec (dllexport) void setSpawn(const char* mapName, int x, int y);

//!设置玩家形象
_declspec (dllexport) void setPlayerAppearance(const char* actorName);