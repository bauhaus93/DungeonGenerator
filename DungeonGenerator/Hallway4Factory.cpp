#include "Hallway4Factory.h"

using namespace std;

Hallway4Factory::Hallway4Factory(const string& idArg, const Size& sizeArg) :
	TileFactory{ idArg, sizeArg }{
}

Hallway4Factory::~Hallway4Factory(){
}


unique_ptr<Tile> Hallway4Factory::Create(Expansion& exp){
	//Rotation will be defined later by expansions
	return make_unique<TileHallway4>(id, exp, size);
}