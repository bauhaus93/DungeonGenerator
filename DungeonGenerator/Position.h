#pragma once

#include "Defs.h"
#include "Point.h"


class Position: public Point{
	
public:
				Position(float xArg, float yArg, float zArg);
				~Position();

	Position	Move(Direction dir, const Size& size);

};

