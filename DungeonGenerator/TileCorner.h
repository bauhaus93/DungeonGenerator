#pragma once

#include <string>
#include <vector>

#include "Tile.h"
#include "Position.h"

class TileCorner: public Tile{

public:
			TileCorner::TileCorner(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
			~TileCorner();

	void	AddValidExpansions(Expansion& srcExp, std::vector<unique_ptr<Expansion>>& expansionList, std::vector<Expansion>& possibleExpansions) override;
	void	Rotate(Direction dir);

};

