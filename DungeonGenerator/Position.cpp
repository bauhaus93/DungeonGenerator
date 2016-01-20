#include "Position.h"



Position::Position(float xArg, float yArg, float zArg):
	x{ xArg },
	y{ yArg },
	z{ zArg }{
}

Position::~Position(){
}

void Position::Move(Direction dir, float scale){
	switch (dir){
		case Direction::NORTH:
			y += scale;
			break;
		case Direction::EAST:
			x += scale;
			break;
		case Direction::SOUTH:
			y -= scale;
			break;
		case Direction::WEST:
			x -= scale;
			break;
		default:
			break;
	}
}
