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

	long AddTileFactory(long dungeon, long type, const char* id, float sizeX, float sizeY, float sizeZ){
		std::string idStr{ id };
		Size size{ sizeX, sizeY, sizeZ };
		if (type < 0 || type > 4)
			return 0l;
		return dungeonHandler->AddTileFactory(dungeon, static_cast<TileType>(type), idStr, size);
	}

	long AddExpansion(long dungeon, float posX, float posY, float posZ, long direction){
		Position pos{ posX, posY, posZ };
		if (direction < 0 || direction > 3)
			return 0l;
		return dungeonHandler->AddExpansion(dungeon, pos, static_cast<Direction>(direction));
	}

	long Generate(long dungeon){
		return dungeonHandler->Generate(dungeon);
	}

	long GetTiles(long dungeon, std::string& id, float& posX, float& posY, float& posZ, float& rotX, float& rotY, float& rotZ){
		auto tile = dungeonHandler->GetTiles(dungeon);
		if (tile){
			id = tile->GetID();
			posX = tile->GetPos().GetX();
			posY = tile->GetPos().GetY();
			posZ = tile->GetPos().GetZ();
			rotX = tile->GetRotation().GetX();
			rotY = tile->GetRotation().GetY();
			rotZ = tile->GetRotation().GetZ();
			return 1l;
		}
		return 0;
	}

}