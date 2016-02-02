#include "TileHallway2.h"

using namespace std;

TileHallway2::TileHallway2(const string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg):
	Tile{ idArg, posArg, sizeArg, rotationArg }{
}

TileHallway2::TileHallway2(const string& idArg, const Position& posArg, const Size& sizeArg):
	Tile{ idArg, posArg, sizeArg }{
}

TileHallway2::~TileHallway2(){

}

void TileHallway2::FilterExpansions(Expansion& srcExp, std::vector<Expansion>& possibleExpansions){
	for (size_t i = 0; i < possibleExpansions.size(); i++){
		if (srcExp.GetDirection() != possibleExpansions[i].GetDirection()){
			possibleExpansions.erase(possibleExpansions.begin() + i);
			i--;
		}
	}
	assert(possibleExpansions.size() == 1);
}

void TileHallway2::Align(Expansion& srcExp, std::vector<Expansion>& expansions){
	switch (srcExp.GetDirection()){
		case Direction::NORTH:
		case Direction::SOUTH:
			rotation.SetZ(0.f);
			break;
		case Direction::EAST:
		case Direction::WEST:
			rotation.SetZ(90.f);
			break;
		default:
			assert(0);
			break;
	}
}