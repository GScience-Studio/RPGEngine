#include "../Engine.h"

int main(int argc, char* argv[])
{
	return run(argc, argv,[]()
	{
		registerActor("example1", "Resource/Actor/example1.atr");
		registerTile("grass", "Resource/Tile/grass.tile");
		registerMap("example", "Resource/Map/example.map", nullptr);
		setSpawn("example", 2, 4);
		setPlayerAppearance("example1");
		return 0;
	});
}