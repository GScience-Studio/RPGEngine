#include "../Engine.h"

int main(int argc, char* argv[])
{
	return run(argc, argv,[]()
	{
		registerTile("grass", "Resource/Tile/grass.tile");
		registerMap("example", "Resource/Map/example.map");
		setSpawn("example", 6, 0);
		return 0;
	});
}