#include "Hallway2Factory.h"

using namespace std;

Hallway2Factory::Hallway2Factory(const string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{
}


Hallway2Factory::~Hallway2Factory(){

}

unique_ptr<Tile> Hallway2Factory::Create(Expansion& exp){
	Rotation rot{};

	switch (exp.GetDirection()){
		case Direction::NORTH:
		case Direction::SOUTH:
			rot[Dim::Z] = 0.f;
			break;
		case Direction::EAST:
		case Direction::WEST:
			rot[Dim::Z] = 90.f;
			break;
		default:
			return NULL;
			break;
	}

	return make_unique<TileHallway2>(id, exp, size, rot);
}
