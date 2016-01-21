#pragma once

#include <vector>
#include <chrono>
#include <random>
#include <map>
#include <sstream>
#include <cmath>
#include <memory>

#include "Communicator.h"
#include "Tile.h"
#include "Position.h"
#include "Defs.h"
#include "TileFactory.h"
#include "Hallway1Factory.h"
#include "Hallway2Factory.h"
#include "Expansion.h"


class DungeonGenerator{

	Communicator					communicator;
	unsigned int					maxSize;
	std::minstd_rand				generator;
	std::vector<Tile>				tiles;
	std::vector<Expansion>			expansions;
	std::map<TileType, std::unique_ptr<TileFactory>>	factory;

	int								Random(int max);
	int								Random(int min, int max);

public:
									DungeonGenerator();
									~DungeonGenerator();

	void							Work();
	void							WriteTiles();
	void							Generate();
	void							AddExpansion(Expansion exp);


	//bool							WouldCollide(const Position & pos);



	


};

