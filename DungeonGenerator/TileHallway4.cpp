#include "TileHallway4.h"

using namespace std;

TileHallway4::TileHallway4(const string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg) :
	Tile{ idArg, posArg, sizeArg, rotationArg }{
}

TileHallway4::TileHallway4(const string& idArg, const Position& posArg, const Size& sizeArg) :
	Tile{ idArg, posArg, sizeArg }{
}


TileHallway4::~TileHallway4(){
}

void TileHallway4::FilterExpansions(Expansion& srcExp, vector<Expansion>& possibleExpansions){
	assert(possibleExpansions.size() == 3);
}

void TileHallway4::Align(Expansion& srcExp, vector<Expansion>& expansions){
	rotation.SetZ(0.f);
}
