#include "../Engine.h"

int main(int argc, char* argv[])
{
	return run(argc, argv,[]()
	{
		registerTile("grass", "Resource/Tile/grass.tile");
		return 0;
	});
}