#pragma once

#include <string>
#include <vector>

#include "Tile.h"
#include "Expansion.h"
#include "CollisionChecker.h"

class TileHallway3: public Tile{
public:
			TileHallway3(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
			TileHallway3(const std::string& idArg, const Position& posArg, const Size& sizeArg);
			~TileHallway3();

	//void	AddValidExpansions(Expansion& srcExp, std::vector<std::unique_ptr<Expansion>>& expansionList, std::vector<Expansion>& possibleExpansions) override;
	void	FilterExpansions(Expansion& srcExp, std::vector<Expansion>& possibleExpansions) override;
	void	Align(Expansion& srcExp, std::vector<Expansion>& expansions) override;
};

