#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TileFactory.h"
#include "Dimension.h"
#include "Expansion.h"
#include "Tile.h"
#include "TileHallway1.h"

class Hallway1Factory: public TileFactory{
public:
				Hallway1Factory(const std::string& idArg, const Size& sizeArg);
				~Hallway1Factory();

	std::unique_ptr<Tile>	Create(Expansion& exp);
};

