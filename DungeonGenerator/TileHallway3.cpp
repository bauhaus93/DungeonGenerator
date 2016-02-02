#include "TileHallway3.h"

using namespace std;

TileHallway3::TileHallway3(const string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg) :
	Tile{ idArg, posArg, sizeArg, rotationArg }{
}

TileHallway3::TileHallway3(const string& idArg, const Position& posArg, const Size& sizeArg) :
	Tile{ idArg, posArg, sizeArg }{
}


TileHallway3::~TileHallway3(){
}

/*void TileHallway3::AddValidExpansions(Expansion& srcExp, vector<unique_ptr<Expansion>>& expansionList, vector<Expansion>& possibleExpansions){

	FilterExpansions(srcExp, possibleExpansions);
	Align(srcExp, possibleExpansions);

	for(Expansion& exp : possibleExpansions)
		expansionList.push_back(make_unique<Expansion>(exp));
}*/

void TileHallway3::FilterExpansions(Expansion& srcExp, vector<Expansion>& possibleExpansions){
	while (possibleExpansions.size() > 2){
		possibleExpansions.erase(possibleExpansions.begin() + common::Random(possibleExpansions.size()));
	}
	assert(possibleExpansions.size() == 2);
}

void TileHallway3::Align(Expansion& srcExp, vector<Expansion>& expansions){
	uint8_t pattern = 0;

	Direction dirA = common::OppositeDirection(srcExp.GetDirection());	//Opposite bc make all directions going out of the object, to make alignment more easy
	Direction dirB = expansions[0].GetDirection();
	Direction dirC = expansions[1].GetDirection();

	for (int i = 0; i < 4; i++){
		Direction dir = static_cast<Direction>(i);
		if (dirA == dir || dirB == dir || dirC == dir)
			pattern |= (1 << i);
	}

	switch (pattern){
		case 1 | 4 | 8:
			rotation.SetZ(0.f);
			break;
		case 1 | 2 | 8:
			rotation.SetZ(90.f);
			break;
		case 1 | 2 | 4:
			rotation.SetZ(180.f);
			break;
		case 2 | 4 | 8:
			rotation.SetZ(270.f);
			break;
		default:
			assert(0);
			break;
	}

}
