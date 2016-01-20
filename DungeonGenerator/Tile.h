#pragma once

#include <string>
#include <sstream>

#include "Position.h"

class Tile{

	std::string		id;
	Position		pos;
	float			zRot;

public:
					Tile(std::string idArg, Position& posArg, float zRotArg);
					~Tile();

	const Position&	GetPos() const;
	float			GetZRot() const { return zRot; };
	std::string		GetID() const	{ return id; };

	std::string		GetString() const;
};

