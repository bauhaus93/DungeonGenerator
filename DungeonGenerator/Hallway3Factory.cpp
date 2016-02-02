#include "Hallway3Factory.h"

using namespace std;

Hallway3Factory::Hallway3Factory(const string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{
}

Hallway3Factory::~Hallway3Factory(){
}


unique_ptr<Tile> Hallway3Factory::Create(Expansion& exp){
	//Rotation will be defined later by expansions
	return make_unique<TileHallway3>(id, exp, size);
}