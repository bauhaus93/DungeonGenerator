#pragma once

#include <vector>
#include <memory>

#include "Position.h"
#include "Defs.h"

class Expansion: public Position{

	Direction		dir;

public:
					Expansion(float x, float y, float z, Direction dirArg);
					Expansion(const Position& pos, Direction dirArg);
					~Expansion();

	Direction		GetDirection() const { return dir; };
	void			SetDirection(Direction newDir){ dir = newDir; };

};

