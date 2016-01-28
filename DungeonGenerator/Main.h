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
	DUNGEON_API long							AddTileFactory(long dungeon, long type, const char* id, float sizeX, float sizeY, float sizeZ);
	DUNGEON_API long							AddExpansion(long dungeon, float posX, float posY, float posZ, long direction);
	DUNGEON_API long							Generate(long dungeon);
	DUNGEON_API long							GetTiles(long dungeon, std::string& id, float& posX, float& posY, float& posZ, float& rotX, float& rotY, float& rotZ);
}