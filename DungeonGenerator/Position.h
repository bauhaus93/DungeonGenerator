#pragma once

#include "Defs.h"
#include "Dimension.h"


class Position: public Dimension{
	
public:
				Position(float x, float y, float z);
				~Position();

	void		Move(Direction dir, const Size& size);

};

