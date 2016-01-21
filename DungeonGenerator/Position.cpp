#include "Position.h"



Position::Position(float xArg, float yArg, float zArg):
	Point(xArg, yArg, zArg){
}

Position::~Position(){
}

Position Position::Move(Direction dir, const Size& size){
	float xNew = x, yNew = y, zNew = z;
	switch (dir){
		case Direction::NORTH:
			xNew += size.GetY();
			break;
		case Direction::EAST:
			yNew += size.GetX();
			break;
		case Direction::SOUTH:
			yNew -= size.GetY();
			break;
		case Direction::WEST:
			xNew -= size.GetX();
			break;
		default:
			break;
	}
	return Position(xNew, yNew, zNew);
}


