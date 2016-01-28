#pragma once

#include <memory>
#include <map>
#include <stdexcept>
#include <exception>
#include <string>

#include "DungeonGenerator.h"

class DungeonHandler{

	std::map<long, std::unique_ptr<DungeonGenerator>>		dungeons;
	long													nextID;

public:
							DungeonHandler();
							~DungeonHandler();
	long					AddDungeon();
	bool					AddTileFactory(long dungeon, TileType type, std::string id, Size& size);
	bool					AddExpansion(long dungeon, Position& pos, Direction dir);
	bool					Generate(long dungeon);
	std::unique_ptr<Tile>	GetTiles(long dungeon);
};

