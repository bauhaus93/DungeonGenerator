#pragma once

#include <Windows.h>

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <random>
#include <map>
#include <sstream>
#include <cmath>
#include <memory>

#include "Tile.h"
#include "Position.h"
#include "Defs.h"
#include "TileFactory.h"
#include "Hallway1Factory.h"
#include "Hallway2Factory.h"
#include "Hallway3Factory.h"
#include "CornerFactory.h"
#include "Expansion.h"
#include "CollisionChecker.h"



class DungeonGenerator{

	std::unique_ptr<CollisionChecker>	collision;
	unsigned int						maxSize;

	std::vector<std::unique_ptr<Tile>>					tiles;
	std::vector<std::unique_ptr<Expansion>>			    expansions;
	std::map<TileType, std::unique_ptr<TileFactory>>	factory;

public:
									DungeonGenerator();
									~DungeonGenerator();

	void							AddTileFactory(TileType type, std::string id, Size& size);

	std::unique_ptr<Tile>			GetTiles();

	void							Generate();
	TileFactory&					GetFactory(Direction currDir, std::vector<Expansion>& possibleExpansions);
	void							GetPossibleExpansions(const Expansion& src, const Size& size, std::vector<Expansion>& possibleExpansions);
	void							AddExpansion(const Expansion& exp);

};

