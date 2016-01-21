#include "Position.h"



Position::Position(float xArg, float yArg, float zArg):
	Point(xArg, yArg, zArg){
}

Position::~Position(){
}

void Position::Move(Direction dir, const Size& size){
	switch (dir){
		case Direction::NORTH:
			y += size.GetY();
			break;
		case Direction::EAST:
			x += size.GetX();
			break;
		case Direction::SOUTH:
			y -= size.GetY();
			break;
		case Direction::WEST:
			x -= size.GetX();
			break;
		default:
			break;
	}
}


