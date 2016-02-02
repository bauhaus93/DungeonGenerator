#include "TileCorner.h"

using namespace std;

TileCorner::TileCorner(const string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg) :
	Tile{ idArg, posArg, sizeArg, rotationArg }{
}

TileCorner::TileCorner(const string& idArg, const Position& posArg, const Size& sizeArg):
	Tile{ idArg, posArg, sizeArg }{
}

TileCorner::~TileCorner(){
}

void TileCorner::FilterExpansions(Expansion& srcExp, vector<Expansion>& possibleExpansions){
	for (size_t i = 0; i < possibleExpansions.size(); i++){
		if (possibleExpansions[i].GetDirection() == srcExp.GetDirection()){
			possibleExpansions.erase(possibleExpansions.begin() + i);
			i--;
		}
		else if (possibleExpansions[i].GetDirection() == common::OppositeDirection(srcExp.GetDirection())){
			possibleExpansions.erase(possibleExpansions.begin() + i);
			i--;
		}
	}
	if(possibleExpansions.size() > 1)
		possibleExpansions.erase(possibleExpansions.begin() + common::Random(possibleExpansions.size()));

	assert(possibleExpansions.size() == 1);
}

void TileCorner::Align(Expansion& srcExp, vector<Expansion>& possibleExpansions){
	uint8_t pattern = 0;

	Direction srcDir = common::OppositeDirection(srcExp.GetDirection());
	Direction destDir = possibleExpansions[0].GetDirection();

	for (int i = 0; i < 4; i++){
		Direction dir = static_cast<Direction>(i);
		if (srcDir == dir ||destDir == dir)
			pattern |= (1 << i);
	}

	switch (pattern){
		case 4 | 8:
			rotation.SetZ(0.f);
			break;
		case 1 | 8:
			rotation.SetZ(90.f);
			break;
		case 1 | 2:
			rotation.SetZ(180.f);
			break;
		case 2 | 4:
			rotation.SetZ(270.f);
			break;
		default:
			assert(0);
			break;
	}
}

/*void TileCorner::AddValidExpansions(Expansion& srcExp, vector<unique_ptr<Expansion>>& expansionList, vector<Expansion>& possibleExpansions){

	for (size_t i = 0; i < possibleExpansions.size(); i++){
		if (possibleExpansions[i].GetDirection() == srcExp.GetDirection()){
			possibleExpansions.erase(possibleExpansions.begin() + i);
		}
		else if (possibleExpansions[i].GetDirection() == common::OppositeDirection(srcExp.GetDirection())){
			possibleExpansions.erase(possibleExpansions.begin() + i);
		}
	}
	assert(possibleExpansions.size() > 0);

	auto& destExp = possibleExpansions.at(common::Random(possibleExpansions.size()));
	auto srcDir = srcExp.GetDirection();
	auto destDir = destExp.GetDirection();
	Align(srcDir, destDir);

	expansionList.push_back(make_unique<Expansion>(destExp));
}*/

