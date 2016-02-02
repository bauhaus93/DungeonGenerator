#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TileFactory.h"
#include "Dimension.h"
#include "Expansion.h"
#include "Tile.h"
#include "TileHallway4.h"

class Hallway4Factory : public TileFactory{

public:
	Hallway4Factory(const std::string& idArg, const Size& sizeArg);
	~Hallway4Factory();

	std::unique_ptr<Tile>	Create(Expansion& exp) override;
};