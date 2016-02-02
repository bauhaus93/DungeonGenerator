#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TileFactory.h"
#include "Dimension.h"
#include "Expansion.h"
#include "Tile.h"
#include "TileHallway3.h"

class Hallway3Factory: public TileFactory{

public:
	Hallway3Factory(const std::string& idArg, const Size& sizeArg);
	~Hallway3Factory();

	std::unique_ptr<Tile>	Create(Expansion& exp) override;
};

