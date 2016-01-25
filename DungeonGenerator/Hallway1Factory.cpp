#include "Hallway1Factory.h"

using namespace std;

Hallway1Factory::Hallway1Factory(const std::string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{
}


Hallway1Factory::~Hallway1Factory(){
}

bool Hallway1Factory::Add(vector<Tile>& tiles, vector<std::unique_ptr<Expansion>>& expansions){
	Rotation rot{};
	unique_ptr<Expansion> exp = move(expansions.back());
	expansions.pop_back();

	switch (exp->GetDirection()){
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
	tiles.push_back(Tile(id, (Position&)*exp, size, rot));
	return true;
}
