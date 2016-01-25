#include "TileHallway2.h"

using namespace std;

TileHallway2::TileHallway2(const string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg):
	Tile{ idArg, posArg, sizeArg, rotationArg }{
}

TileHallway2::~TileHallway2(){

}

int TileHallway2::AddExpansions(Expansion& srcExp, vector<unique_ptr<Expansion>>& expansionList){
	auto exp = make_unique<Expansion>(pos, srcExp.GetDirection());
	exp->Move(exp->GetDirection(), size);
	expansionList.push_back(move(exp));
	return 1;
}

