#include "TileCorner.h"

using namespace std;

TileCorner::TileCorner(const string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg) :
	Tile{ idArg, posArg, sizeArg, rotationArg }{
}


TileCorner::~TileCorner(){
}

void TileCorner::AddValidExpansions(Expansion& srcExp, vector<unique_ptr<Expansion>>& expansionList, vector<Expansion>& possibleExpansions){
	
	/*cout << "src is " << common::DirString(srcExp.GetDirection()) << endl;
	for (auto& exp : possibleExpansions){
		cout << " possible: " << common::DirString(exp.GetDirection()) << endl;
	}*/

	for (size_t i = 0; i < possibleExpansions.size(); i++){
		if (possibleExpansions[i].GetDirection() == srcExp.GetDirection()){
			possibleExpansions.erase(possibleExpansions.begin()+i);
		}
		else if (possibleExpansions[i].GetDirection() == common::OppositeDirection(srcExp.GetDirection())){
			possibleExpansions.erase(possibleExpansions.begin() + i);
		}
	}
	if (possibleExpansions.size() == 0)
		return;
	auto& destExp = possibleExpansions.at(common::Random(possibleExpansions.size()));
	auto srcDir = srcExp.GetDirection();
	auto destDir = destExp.GetDirection();
	Align(srcDir, destDir);
	//cout << "pushing " <<  common::DirString(srcDir) << " -> " << common::DirString(destDir) << endl;
	expansionList.push_back(make_unique<Expansion>(destExp));
}

void TileCorner::Align(Direction srcDir, Direction destDir){

	switch (srcDir){
		case Direction::NORTH:
			if (destDir == Direction::EAST)
				rotation.SetZ(270.f);
			else if(destDir == Direction::WEST)
				rotation.SetZ(0.f);
			break;
		case Direction::EAST:
			if (destDir == Direction::NORTH)
				rotation.SetZ(90.f);
			else if (destDir == Direction::SOUTH)
				rotation.SetZ(0.f);
			break;
		case Direction::SOUTH:
			if (destDir == Direction::EAST)
				rotation.SetZ(180.f);
			else if (destDir == Direction::WEST)
				rotation.SetZ(90.f);
			break;
		case Direction::WEST:
			if (destDir == Direction::NORTH)
				rotation.SetZ(180.f);
			else if (destDir == Direction::SOUTH)
				rotation.SetZ(270.f);
			break;
		default:
			break;
	}
}


