#pragma once

#include <vector>
#include <memory>

#include "Tile.h"
#include "Expansion.h"
#include "Position.h"

class CollisionChecker{

	const std::vector<std::unique_ptr<Tile>>&		tiles;
	const std::vector<std::unique_ptr<Expansion>>&	expansions;

	bool	Collides(const Position& posA, const Size& sizeA, const Position& posB, const Size& sizeB);
	bool	CheckCoordinate(float dimA, float sizeA, float dimB, float sizeB);

public:
			CollisionChecker(const std::vector<std::unique_ptr<Tile>>& tilesArg, const std::vector<std::unique_ptr<Expansion>>& expansionsArg);
			~CollisionChecker();
	bool	ValidateDungeon();
	bool	Check(const Position& pos, const Size& size);
	bool	Recheck();
	
};

inline bool CollisionChecker::CheckCoordinate(float dimA, float sizeA, float dimB, float sizeB){
	if (abs(dimA - dimB) < ((sizeA / 2) + (sizeB / 2)))
		return true;
	return false;
}