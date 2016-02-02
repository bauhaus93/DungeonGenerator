#pragma once

#include <string>

#include "Tile.h"
#include "Expansion.h"
#include "CollisionChecker.h"

class TileHallway3: public Tile{
public:
			TileHallway3(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
			~TileHallway3();

	void	AddValidExpansions(Expansion& srcExp, std::vector<std::unique_ptr<Expansion>>& expansionList, std::vector<Expansion>& possibleExpansions) override;
	void	Align(Direction srcDir, Direction dirA, Direction dirB);
};

