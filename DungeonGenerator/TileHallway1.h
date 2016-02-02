#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Tile.h"
#include "Expansion.h"
#include "CollisionChecker.h"

class TileHallway1:	public Tile{


public:
			TileHallway1(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
			TileHallway1(const std::string& idArg, const Position & posArg, const Size & sizeArg);
			~TileHallway1();

	void	FilterExpansions(Expansion& srcExp, std::vector<Expansion>& possibleExpansions) override;
	void	Align(Expansion& srcExp, std::vector<Expansion>& expansions) override;
};