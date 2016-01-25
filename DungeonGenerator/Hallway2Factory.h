#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TileFactory.h"
#include "Dimension.h"
#include "Expansion.h"
#include "Tile.h"
#include "TileHallway2.h"

class Hallway2Factory :	public TileFactory{

public:
							Hallway2Factory(const std::string& idArg, const Size& sizeArg);
							~Hallway2Factory();

	std::unique_ptr<Tile>	Create(Expansion& exp) override;
};

