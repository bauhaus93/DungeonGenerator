#include "Position.h"



Position::Position(float x, float y, float z):
	Dimension(x, y, z){
}

Position::~Position(){
}

void Position::Move(Direction dir, const Size& size){
	switch (dir){
		case Direction::NORTH:
			ModY(size.GetY());
			break;
		case Direction::EAST:
			ModX(size.GetX());
			break;
		case Direction::SOUTH:
			ModY(-size.GetY());
			break;
		case Direction::WEST:
			ModX(-size.GetX());
			break;
		default:
			break;
	}
}


