#pragma once

enum class Direction{ NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };
enum class TileType{ HALL1, HALL2, HALL3, HALL4, CORNER };
enum class Dim{ X = 0, Y = 1, Z = 2 };

namespace common{
	inline Direction OppositeDirection(Direction dir){
		switch (dir){
		case Direction::NORTH:	return Direction::SOUTH;
		case Direction::SOUTH: return Direction::NORTH;
		case Direction::EAST: return Direction::WEST;
		case Direction::WEST: return Direction::EAST;
		}
	}
}