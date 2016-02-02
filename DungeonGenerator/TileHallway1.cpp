#include "TileHallway1.h"

using namespace std;

TileHallway1::TileHallway1(const string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg):
	Tile{ idArg, posArg, sizeArg, rotationArg }{
}

TileHallway1::TileHallway1(const string& idArg, const Position& posArg, const Size& sizeArg) :
	Tile{ idArg, posArg, sizeArg }{
}


TileHallway1::~TileHallway1(){
}

void TileHallway1::FilterExpansions(Expansion & srcExp, std::vector<Expansion>& possibleExpansions){
	possibleExpansions.clear();
	assert(possibleExpansions.size() == 0);
}

void TileHallway1::Align(Expansion& srcExp, std::vector<Expansion>& expansions){
	switch (srcExp.GetDirection()){
		case Direction::NORTH:
			rotation.SetZ(180.f);
			break;
		case Direction::EAST:
			rotation.SetZ(270.f);
			break;
		case Direction::SOUTH:
			rotation.SetZ(0.f);
			break;
		case Direction::WEST:
			rotation.SetZ(90.f);
			break;
		default:
			assert(0);
			break;
	}
}



