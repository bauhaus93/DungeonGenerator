#pragma once

#include <vector>
#include <chrono>
#include <random>
#include <map>
#include <sstream>
#include <cmath>

#include "Communicator.h"
#include "Tile.h"
#include "Position.h"
#include "Defs.h"


class DungeonGenerator{

	Communicator		communicator;
	short				scale;
	unsigned int		maxSize;
	std::minstd_rand	generator;
	std::vector<Tile>	tiles;
	std::map<TileType, std::string>	tileIDs;

	int					Random(int max);
	int					Random(int min, int max);

public:
						DungeonGenerator();
						~DungeonGenerator();

	void				Work();
	void				WriteTiles();
	void				Generate(Position& pos, Direction dir);
	void				MakeHallway1(Position& pos, Direction dir);
	void				MakeHallway2(Position& pos, Direction dir, int length);
	void				MakeHallway3(Position& pos, Direction dir);
	void				MakeCorner(Position& pos, Direction& dir);
	bool				CalculateCorner(Position& pos, Direction& dir, Direction toA, Direction toB, float& zRot);

	bool				WouldCollide(const Position & pos);

	int					FreeSpace(Position pos, Direction dir, int times);

	bool				CornerPossible(Position pos, Direction newDir);

	


};

