#include "Hallway2Factory.h"

using namespace std;

Hallway2Factory::Hallway2Factory(const string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{
}


Hallway2Factory::~Hallway2Factory(){

}

unique_ptr<Tile> Hallway2Factory::Create(Expansion& exp){
	return make_unique<TileHallway2>(id, exp, size);
}
