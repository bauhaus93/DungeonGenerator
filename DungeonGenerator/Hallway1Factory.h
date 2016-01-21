#pragma once

#include <string>
#include <vector>

#include "TileFactory.h"
#include "Point.h"
#include "Expansion.h"

class Hallway1Factory: public TileFactory{
public:
				Hallway1Factory(const std::string& idArg, const Size& sizeArg);
				~Hallway1Factory();

		bool	Add(Expansion & expansion, std::vector<Tile> tiles, std::vector<Expansion> expansions);
};

