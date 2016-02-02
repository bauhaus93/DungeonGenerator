#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "Tile.h"
#include "Position.h"
#include "Expansion.h"

class TileCorner: public Tile{

public:
					TileCorner(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
					TileCorner(const std::string& idArg, const Position& posArg, const Size& sizeArg);
					~TileCorner();

	//void	AddValidExpansions(Expansion& srcExp, std::vector<std::unique_ptr<Expansion>>& expansionList, std::vector<Expansion>& possibleExpansions) override;
	virtual void	FilterExpansions(Expansion& srcExp, std::vector<Expansion>& possibleExpansions);
	virtual void	Align(Expansion& srcExp, std::vector<Expansion>& possibleExpansions);

};

