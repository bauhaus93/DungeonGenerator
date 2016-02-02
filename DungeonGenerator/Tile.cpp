#include "Tile.h"

using namespace std;

Tile::Tile(const string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg):
	id{ idArg },
	pos{ posArg },
	size{ sizeArg },
	rotation{ rotationArg }{

}

Tile::Tile(const string& idArg, const Position& posArg, const Size& sizeArg):
	id{ idArg },
	pos{ posArg },
	size{ sizeArg },
	rotation{ }{

}

Tile::~Tile(){
}

void Tile::AddValidExpansions(Expansion & srcExp, std::vector<std::unique_ptr<Expansion>>& expansionList, std::vector<Expansion>& possibleExpansions){
	FilterExpansions(srcExp, possibleExpansions);
	
	Align(srcExp, possibleExpansions);

	for (Expansion& exp : possibleExpansions)
		expansionList.push_back(make_unique<Expansion>(exp));
}

string Tile::GetString() const{
	ostringstream str;
	str << "tile: " << GetID() << " (" << pos.GetX() << "/" << pos.GetY() << "/" << pos.GetZ() << "), rot = " << rotation[Dim::Z];
	return string(str.str());
}

