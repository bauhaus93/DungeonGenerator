#define DUNGEON_EXPORTS
#include "Main.h"

FILE *outStream;

static DungeonHandler* dungeonHandler;

BOOLEAN WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved){
	BOOLEAN bSuccess = TRUE;


	switch (nReason){
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen_s(&outStream, "CONOUT$", "w", stdout);
		dungeonHandler = new DungeonHandler();
		DisableThreadLibraryCalls(hDllHandle);
		break;
	case DLL_PROCESS_DETACH:
		delete dungeonHandler;
		FreeConsole();
		break;
	}

	return bSuccess;
}

namespace DungeonDll{

	long GetDungeon(){
		return dungeonHandler->AddDungeon();
	}

	bool AddTileFactory(long dungeon, TileType type, std::string id, Size& size){
		return dungeonHandler->AddTileFactory(dungeon, type, id, size);
	}

	bool AddExpansion(long dungeon, Position& pos, Direction dir){
		return dungeonHandler->AddExpansion(dungeon, pos, dir);
	}

	bool Generate(long dungeon){
		return dungeonHandler->Generate(dungeon);
	}
	std::unique_ptr<Tile> GetTiles(long dungeon){
		return dungeonHandler->GetTiles(dungeon);
	}

}