#include "TileCorner.h"

using namespace std;

TileCorner::TileCorner(const string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg) :
	Tile{ idArg, posArg, sizeArg, rotationArg }{
}


TileCorner::~TileCorner(){
}

void TileCorner::AddValidExpansions(Expansion& srcExp, vector<unique_ptr<Expansion>>& expansionList, vector<Expansion>& possibleExpansions){
	for (auto& possibleExp : possibleExpansions){
		if (srcExp.GetDirection() == possibleExp.GetDirection()){
			expansionList.push_back(make_unique<Expansion>(possibleExp));
			break;
		}
	}
}

void TileCorner::Rotate(Direction dir){

}
