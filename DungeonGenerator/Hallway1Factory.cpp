#include "Hallway1Factory.h"

using namespace std;

Hallway1Factory::Hallway1Factory(const string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{
}


Hallway1Factory::~Hallway1Factory(){
}

unique_ptr<Tile> Hallway1Factory::Create(Expansion& exp){
	//Rotation will be defined later by expansions
	return make_unique<TileHallway1>(id, exp, size);
}
