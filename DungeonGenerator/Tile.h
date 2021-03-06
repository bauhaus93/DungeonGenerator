#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>

#include <assert.h>

#include "Position.h"
#include "Expansion.h"

class Tile{

protected:
	std::string		id;
	Position		pos;
	Size			size;
	Rotation		rotation;

public:
					Tile(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
					Tile(const std::string & idArg, const Position & posArg, const Size & sizeArg);
	virtual			~Tile();

	//precondition: the called tile can be placed rightful
	void			AddValidExpansions(Expansion& srcExp, std::vector<std::unique_ptr<Expansion>>& expansionList, std::vector<Expansion>& possibleExpansions);
	virtual void	FilterExpansions(Expansion& srcExp, std::vector<Expansion>& possibleExpansions) = 0;
	virtual void	Align(Expansion& srcExp, std::vector<Expansion>& possibleExpansions) = 0;


	const Position&	GetPos()		const;
	const Size&		GetSize()		const;
	const Rotation& GetRotation()	const;
	std::string		GetID()			const;

	std::string		GetString()		const;
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

