#pragma once

#include <string>
#include <vector>
#include <memory>

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
	virtual			~TileFactory();

	virtual bool	Add(std::vector<Tile>& tiles, std::vector<std::unique_ptr<Expansion>>& expansions) = 0;

};

