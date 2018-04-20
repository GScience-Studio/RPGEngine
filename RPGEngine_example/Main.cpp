#include "../Engine.h"

class ExampleMap :public GameMapEventProcessorBase
{

};

int main(int argc, char* argv[])
{
	ExampleMap exampleMap;

	return run(argc, argv,[&]()
	{
		registerActorAppearance("example1", "Resource/Actor/example1.atr");
		registerActorAppearance("example2", "Resource/Actor/example2.atr");
		registerTile("grass", "Resource/Tile/grass.tile");
		registerTile("lava_pool", "Resource/Tile/lava_pool.tile");
		registerMap("example", "Resource/Map/example.map", &exampleMap);
		setSpawn("example", 2, 4, 1);
		setPlayerAppearance("example1");
		return 0;
	});
}