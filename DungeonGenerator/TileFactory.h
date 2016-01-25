#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Dimension.h"
#include "Position.h"
#include "Tile.h"
#include "Expansion.h"

class TileFactory{

protected:
	std::string		id;
	Size			size;

public:
									TileFactory(const std::string& idArg, const Size& sizeArg);
	virtual							~TileFactory();

	virtual std::unique_ptr<Tile>	Create(Expansion& exp) = 0;

	const Size&						GetSize() const{ return size; };

};

