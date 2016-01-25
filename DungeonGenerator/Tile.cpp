#include "Tile.h"

using namespace std;

Tile::Tile(const string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg):
	id{ idArg },
	pos{ posArg },
	size{ sizeArg },
	rotation{ rotationArg }{

}

Tile::~Tile(){
}



string Tile::GetString() const{
	ostringstream str;
	str << "tile: " << GetID() << " (" << pos.GetX() << "/" << pos.GetY() << "/" << pos.GetZ() << "), rot = " << rotation[Dim::Z];
	return string(str.str());
}
