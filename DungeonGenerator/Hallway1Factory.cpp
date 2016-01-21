#include "Hallway1Factory.h"

using namespace std;

Hallway1Factory::Hallway1Factory(const std::string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{
}


Hallway1Factory::~Hallway1Factory(){
}

bool Hallway1Factory::Add(Expansion & expansion, vector<Tile> tiles, vector<Expansion> expansions){
	float zRot;

	switch (expansion.GetDirection()){
		case Direction::NORTH:
			zRot = 180.f;
			break;
		case Direction::EAST:
			zRot = 270.f;
			break;
		case Direction::SOUTH:
			zRot = 0.f;
			break;
		case Direction::WEST:
			zRot = 90.f;
			break;
		default:
			return false;
	}
	tiles.push_back(Tile(id, expansion, zRot));
	return true;
}
