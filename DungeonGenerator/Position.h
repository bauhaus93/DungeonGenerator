#pragma once

#include "Defs.h"


class Position{

	float		x;
	float		y;
	float		z;

public:
				Position(float xArg, float yArg, float zArg);
				~Position();

	float		GetX() const { return x; };
	float		GetY() const { return y; };
	float		GetZ() const { return z; };

	void		Set(float xNew, float yNew, float zNew){};
	void		SetX(float xNew){ x = xNew; };
	void		SetY(float yNew){ y = yNew; };
	void		SetZ(float zNew){ z = zNew; };

	void		Move(Direction dir, float scale);

};

