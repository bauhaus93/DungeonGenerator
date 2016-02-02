#pragma once


#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>
#include <random>

#include "Enums.h"

static std::minstd_rand generator;
static std::chrono::high_resolution_clock timer;

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

	inline std::chrono::time_point<std::chrono::steady_clock> Time(){
		return timer.now();
	}

	extern std::string TimeDiff(std::chrono::time_point<std::chrono::steady_clock> start);

}