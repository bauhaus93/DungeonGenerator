#pragma once

#include "TileFactory.h"
#include "TileCorner.h"

class CornerFactory: public TileFactory{
public:

							CornerFactory(const std::string& idArg, const Size& sizeArg);
							~CornerFactory();
	std::unique_ptr<Tile>	Create(Expansion& exp) override;
};

