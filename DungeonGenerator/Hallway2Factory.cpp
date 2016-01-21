#include "Hallway2Factory.h"

using namespace std;

Hallway2Factory::Hallway2Factory(const string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{
}


Hallway2Factory::~Hallway2Factory(){

}

bool Hallway2Factory::Add(vector<Tile>& tiles, vector<unique_ptr<Expansion>>& expansions){
	float zRot;
	unique_ptr<Expansion> exp = move(expansions.back());
	expansions.pop_back();

	switch (exp->GetDirection()){
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

	tiles.push_back(Tile(id, (Position&)*exp, zRot));
	exp->Move(exp->GetDirection(), size);
	expansions.push_back(move(exp));

	return true;
}
