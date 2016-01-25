#pragma once

#include "Position.h"
#include "Defs.h"

class Expansion: public Position{

	Direction		dir;

public:
					Expansion(float x, float y, float z, Direction dirArg);
					Expansion(const Position& pos, Direction dirArg);
					~Expansion();

	Direction		GetDirection(){ return dir; };
};

