#pragma once

#include <string>
#include <vector>

#include "TileFactory.h"
#include "Point.h"
#include "Expansion.h"

class Hallway2Factory :	public TileFactory{

public:
			Hallway2Factory(const std::string& idArg, const Size& sizeArg);
			~Hallway2Factory();

	bool	Add(Expansion & expansion, std::vector<Tile> tiles, std::vector<Expansion> expansions);
};

