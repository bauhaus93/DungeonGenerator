#pragma once

#include <string>

#include "Tile.h"
#include "Expansion.h"


class TileHallway2 :
	public Tile{
public:
			TileHallway2(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
			~TileHallway2();

	int		AddExpansions(Expansion& srcExp, std::vector<std::unique_ptr<Expansion>>& expansionList) override;
};

