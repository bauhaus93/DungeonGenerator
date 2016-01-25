#include "TileHallway2.h"

using namespace std;

TileHallway2::TileHallway2(const string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg):
	Tile{ idArg, posArg, sizeArg, rotationArg }{
}

TileHallway2::~TileHallway2(){

}

void TileHallway2::AddValidExpansions(Expansion& srcExp, vector<unique_ptr<Expansion>>& expansionList, vector<Expansion>& possibleExpansions){
	for (auto& possibleExp : possibleExpansions){
		if (srcExp.GetDirection() == possibleExp.GetDirection()){
			expansionList.push_back(make_unique<Expansion>(possibleExp));
			break;
		}
	}
}

