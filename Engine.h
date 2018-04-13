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

/*!��ʼ��
 * @note ��Ҫ����������ǰע�����tile��map������Ϸ�йصĶ���
 * һ��ִ�У�����Ϸ�ͻ���ʽ��ʼ
 */
_declspec (dllexport) int run(int argc, char* argv[], const std::function<int()>& initFunc);

//!ע��tile
_declspec (dllexport) void registerTile(const char* tileName, const char* fileName);

//!ע��map
_declspec (dllexport) void registerMap(const char* mapName, const char* fileName, GameMapEventProcessorBase* eventProcessor);

//!ע��actor
_declspec (dllexport) void registerActor(const char* actorName, const char* fileName);

//!���ÿ�ʼ��Ϸʱ��λ��
_declspec (dllexport) void setSpawn(const char* mapName, int x, int y);

//!�����������
_declspec (dllexport) void setPlayerAppearance(const char* actorName);