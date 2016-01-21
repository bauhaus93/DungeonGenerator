#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TileFactory.h"
#include "Point.h"
#include "Expansion.h"
#include "Tile.h"

class Hallway2Factory :	public TileFactory{

public:
			Hallway2Factory(const std::string& idArg, const Size& sizeArg);
			~Hallway2Factory();

	bool	Add(std::vector<Tile>& tiles, std::vector<std::unique_ptr<Expansion>>& expansions) override;
};

