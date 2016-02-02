#pragma once

#include <string>
#include <vector>

#include "Tile.h"
#include "Expansion.h"
#include "CollisionChecker.h"

class TileHallway4 : public Tile{
public:
	TileHallway4(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
	TileHallway4(const std::string& idArg, const Position& posArg, const Size& sizeArg);
	~TileHallway4();

	void	FilterExpansions(Expansion& srcExp, std::vector<Expansion>& possibleExpansions) override;
	void	Align(Expansion& srcExp, std::vector<Expansion>& expansions) override;
};

