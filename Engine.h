#pragma once

#include <functional>
#include <SDL2/SDL_main.h>

#define TILE_SIZE 64

#define XTILE_COUNT 16
#define YTILE_COUNT 12

#define WINDOW_WIDTH (TILE_SIZE * XTILE_COUNT)
#define WINDOW_HEIGHT (TILE_SIZE * YTILE_COUNT)

/*!��ʼ��
 * @note ��Ҫ����������ǰע�����tile��map������Ϸ�йصĶ���
 * һ��ִ�У�����Ϸ�ͻ���ʽ��ʼ
 */
_declspec (dllexport) int run(int argc, char* argv[], const std::function<int()>& initFunc);

//!ע��tile
_declspec (dllexport) void registerTile(const char* tileName, const char* fileName);

//!ע��map
_declspec (dllexport) void registerMap(const char* mapName, const char* fileName);

//!���ÿ�ʼ��Ϸʱ��λ��
_declspec (dllexport) void setSpawn(const char* mapName, int x, int y);