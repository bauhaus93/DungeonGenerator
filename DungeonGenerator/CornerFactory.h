#pragma once

#include "TileFactory.h"

class CornerFactory: public TileFactory{
public:

					CornerFactory(const std::string& idArg, const Size& sizeArg);
					~CornerFactory();
	bool			Add(std::vector<Tile>& tiles, std::vector<std::unique_ptr<Expansion>>& expansions);
};

