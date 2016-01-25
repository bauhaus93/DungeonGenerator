#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TileFactory.h"
#include "Dimension.h"
#include "Expansion.h"
#include "Tile.h"

class Hallway1Factory: public TileFactory{
public:
				Hallway1Factory(const std::string& idArg, const Size& sizeArg);
				~Hallway1Factory();

    bool		Add(std::vector<Tile>& tiles, std::vector<std::unique_ptr<Expansion>>& expansions) override;
};

