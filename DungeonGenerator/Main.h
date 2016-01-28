#pragma once

#ifdef DUNGEON_EXPORTS
#define	DUNGEON_API __declspec(dllexport)
#else
#define DUNGEON_API __declspec(dllimport)
#endif

#include <windows.h>
#include <string>
#include <iostream>
#include <memory>

#include "DungeonGenerator.h"
#include "DungeonHandler.h"

namespace DungeonDll{
	DUNGEON_API long							GetDungeon();
	DUNGEON_API bool							AddTileFactory(long dungeon, TileType type, std::string id, Size& size);
	DUNGEON_API bool							AddExpansion(long dungeon, Position& pos, Direction dir);
	DUNGEON_API bool							Generate(long dungeon);
	DUNGEON_API std::unique_ptr<Tile>			GetTiles(long dungeon);
}