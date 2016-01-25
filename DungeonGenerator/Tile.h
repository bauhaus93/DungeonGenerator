#pragma once

#include <string>
#include <sstream>
#include <memory>

#include "Position.h"
#include "Expansion.h"

class Tile{

	std::string		id;
	Position		pos;
	Size			size;
	Rotation		rotation;

public:
					Tile(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
					~Tile();

	const Position&	GetPos()		const;
	const Size&		GetSize()		const;
	const Rotation& GetRotation()	const;
	std::string		GetID()			const;

	std::string		GetString() const;
};

inline const Position& Tile::GetPos() const{
	return pos;
}

inline const Size& Tile::GetSize() const{
	return size;
}

inline const Rotation& Tile::GetRotation() const{
	return rotation;
};

inline std::string Tile::GetID() const{
	return id;
};

