#include "Hallway1Factory.h"

using namespace std;

Hallway1Factory::Hallway1Factory(const string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{
}


Hallway1Factory::~Hallway1Factory(){
}

unique_ptr<Tile> Hallway1Factory::Create(Expansion& exp){
	Rotation rot{};

	switch (exp.GetDirection()){
		case Direction::NORTH:
			rot[Dim::Z] = 180.f;
			break;
		case Direction::EAST:
			rot[Dim::Z] = 270.f;
			break;
		case Direction::SOUTH:
			rot[Dim::Z] = 0.f;
			break;
		case Direction::WEST:
			rot[Dim::Z] = 90.f;
			break;
		default:
			return false;
	}
	return make_unique<TileHallway1>(id, exp, size, rot);
}
