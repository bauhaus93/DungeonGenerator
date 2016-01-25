#pragma once

#include <iostream>
#include <iomanip>
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
#include "CornerFactory.h"
#include "Expansion.h"
#include "CollisionChecker.h"


class DungeonGenerator{

	Communicator					communicator;
	std::unique_ptr<CollisionChecker>	collision;
	unsigned int					maxSize;
	std::minstd_rand				generator;
	std::vector<std::unique_ptr<Tile>>					tiles;
	std::vector<std::unique_ptr<Expansion>>			    expansions;
	std::map<TileType, std::unique_ptr<TileFactory>>	factory;

	int								Random(int max);
	int								Random(int min, int max);

public:
									DungeonGenerator();
									~DungeonGenerator();

	void							Work();
	void							WriteTiles();
	void							Generate();
	TileFactory&					GetFactory();
	void							GetPossibleExpansions(const Expansion& src, const Size& size, std::vector<Expansion>& possibleExpansions);
	void							AddExpansion(const Expansion& exp);

};

inline int DungeonGenerator::Random(int max){
	return generator() % max;
}

inline int DungeonGenerator::Random(int min, int max){
	return min + Random(max - min + 1);
}