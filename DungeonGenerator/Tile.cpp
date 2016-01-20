#include "Tile.h"

using namespace std;

Tile::Tile(string idArg, Position& posArg, float zRotArg):
	id{ idArg },
	pos{ posArg },
	zRot{ zRotArg }{

}


Tile::~Tile(){
}

const Position& Tile::GetPos() const{
	return pos;
}

string Tile::GetString() const{
	ostringstream str;
	str << "tile: " << GetID() << " (" << pos.GetX() << "/" << pos.GetY() << "/" << pos.GetZ() << "), rot = " << GetZRot();
	return string(str.str());
}
