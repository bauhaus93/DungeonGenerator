#pragma once

#include <string>
#include <vector>

#include "Point.h"
#include "Position.h"
#include "Tile.h"
#include "Expansion.h"

class TileFactory{

protected:
	std::string		id;
	Size			size;

public:
					TileFactory(const std::string& idArg, const Size& sizeArg);
					~TileFactory();

	virtual bool	TileFactory::Add(Expansion & expansion, std::vector<Tile> tiles, std::vector<Expansion> expansions) = 0;
};

