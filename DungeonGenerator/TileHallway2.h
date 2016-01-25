#pragma once

#include <string>

#include "Tile.h"
#include "Expansion.h"
#include "CollisionChecker.h"


class TileHallway2 :
	public Tile{
public:
			TileHallway2(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
			~TileHallway2();

	void	AddValidExpansions(Expansion& srcExp, std::vector<std::unique_ptr<Expansion>>& expansionList, std::vector<Expansion>& possibleExpansions) override;
};
