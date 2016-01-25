#include "Hallway2Factory.h"

using namespace std;

Hallway2Factory::Hallway2Factory(const string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{
}


Hallway2Factory::~Hallway2Factory(){

}

bool Hallway2Factory::Add(vector<Tile>& tiles, vector<unique_ptr<Expansion>>& expansions){
	Rotation rot{};

	unique_ptr<Expansion> exp = move(expansions.back());
	expansions.pop_back();

	switch (exp->GetDirection()){
		case Direction::NORTH:
		case Direction::SOUTH:
			rot[Dim::Z] = 0.f;
			break;
		case Direction::EAST:
		case Direction::WEST:
			rot[Dim::Z] = 90.f;
			break;
		default:
			return false;
			break;
	}

	tiles.push_back(Tile(id, (Position&)*exp, size, rot));
	exp->Move(exp->GetDirection(), size);
	expansions.push_back(move(exp));

	return true;
}
