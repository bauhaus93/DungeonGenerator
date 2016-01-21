#pragma once

#include <string>
#include <sstream>
#include <memory>

#include "Position.h"
#include "Expansion.h"

class Tile{

	std::string		id;
	Position		pos;
	float			zRot;

public:
					Tile(std::string idArg, Position& posArg, float zRotArg);
					Tile(std::string idArg, std::unique_ptr<Expansion> posArg, float zRotArg);
					~Tile();

	const Position&	GetPos() const;
	float			GetZRot() const { return zRot; };
	std::string		GetID() const	{ return id; };

	std::string		GetString() const;
};

