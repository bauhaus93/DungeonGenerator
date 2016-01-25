#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Tile.h"
#include "Expansion.h"

class TileHallway1:	public Tile{


public:
			TileHallway1(const std::string& idArg, const Position& posArg, const Size& sizeArg, const Rotation& rotationArg);
			~TileHallway1();

	int		AddExpansions(Expansion& srcExp, std::vector<std::unique_ptr<Expansion>>& expansionList) override;

};

inline int TileHallway1::AddExpansions(Expansion& srcExp, std::vector<std::unique_ptr<Expansion>>& expansionList){
	return 0;
}