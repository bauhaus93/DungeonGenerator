#pragma once

#include <string>

#include "Tile.h"
#include "Expansion.h"
#include "CollisionChecker.h"


class TileHallway2 :
	public Tile{
public:
			TileHallway2(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
			TileHallway2(const std::string& idArg, const Position& posArg, const Size& sizeArg);
			~TileHallway2();

	void	FilterExpansions(Expansion& srcExp, std::vector<Expansion>& possibleExpansions) override;
	void	Align(Expansion& srcExp, std::vector<Expansion>& expansions) override;
};

