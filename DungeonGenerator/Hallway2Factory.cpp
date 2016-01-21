#include "Hallway2Factory.h"



Hallway2Factory::Hallway2Factory(const std::string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{
}


Hallway2Factory::~Hallway2Factory(){

}

bool Hallway2Factory::Add(Expansion & expansion, std::vector<Tile> tiles, std::vector<Expansion> expansions){
	float zRot;

	switch (expansion.GetDirection()){
		case Direction::NORTH:
		case Direction::SOUTH:
			zRot = 0;
			break;
		case Direction::EAST:
		case Direction::WEST:
			zRot = 90;
			break;
		default:
			return false;
			break;
	}

	tiles.push_back(Tile(id, expansion, zRot));
	expansions.push_back(Expansion(expansion.Move(expansion.GetDirection(), size), expansion.GetDirection()));

	return true;
}
