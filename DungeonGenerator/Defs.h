#pragma once

#include <string>
#include <chrono>
#include <random>

enum class Direction{ NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };
enum class TileType{ HALL1, HALL2, HALL3, HALL4, CORNER };
enum class Dim{ X = 0, Y = 1, Z = 2 };

static std::minstd_rand generator;

namespace common{

	inline Direction OppositeDirection(Direction dir){
		switch (dir){
		case Direction::NORTH:	return Direction::SOUTH;
		case Direction::SOUTH: return Direction::NORTH;
		case Direction::EAST: return Direction::WEST;
		case Direction::WEST: return Direction::EAST;
		}
	}

	inline std::string DirString(Direction dir){
		switch (dir){
		case Direction::NORTH:	return "NORTH";
		case Direction::SOUTH: return  "SOUTH";
		case Direction::EAST: return "EAST";
		case Direction::WEST: return "WEST";
		}
	}

	inline void Randomize(){
		generator.seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
	}

	inline int Random(int max){
		return generator() % max;
	}

	inline int Random(int min, int max){
		return min + Random(max - min + 1);
	}
}