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
			~TileHallway1();

	void	AddValidExpansions(Expansion& srcExp, std::vector<std::unique_ptr<Expansion>>& expansionList, std::vector<Expansion>& possibleExpansions) override;

};

inline void TileHallway1::AddValidExpansions(Expansion& srcExp, std::vector<std::unique_ptr<Expansion>>& expansionList, std::vector<Expansion>& possibleExpansions){
}