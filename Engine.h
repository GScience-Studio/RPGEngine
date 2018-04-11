#pragma once

#include <functional>
#include <SDL2/SDL_main.h>

/*!��ʼ��
 * @note ��Ҫ����������ǰע�����tile��map������Ϸ�йصĶ���
 * һ��ִ�У�����Ϸ�ͻ���ʽ��ʼ
 */
_declspec (dllexport) int run(int argc, char* argv[], const std::function<int()>& initFunc);

//!ע��tile
_declspec (dllexport) void registerTile(const char* tileName, const char* fileName);

//!ע��map
_declspec (dllexport) void registerMap(const char* fileName);