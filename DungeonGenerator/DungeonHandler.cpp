#include "DungeonHandler.h"

using namespace std;

DungeonHandler::DungeonHandler():
	nextID{ 1 }{
	cout << "DungeonHandler initalized!" << endl;
}


DungeonHandler::~DungeonHandler(){

}

long DungeonHandler::AddDungeon(){
	dungeons.insert(make_pair(nextID, make_unique<DungeonGenerator>()));
	cout << "Created Dungeon with ID " << nextID << endl;
	return nextID++;
}

bool DungeonHandler::AddTileFactory(long dungeon, TileType type, string id, Size& size){
	try{
		cout << "adding tilefactory \"" << id << "\", type: " << static_cast<int>(type) << ", size: " << size[Dim::X] << "/" << size[Dim::Y] << "/" << size[Dim::Z] << endl;
		dungeons.at(dungeon)->AddTileFactory(type, id, size);
	}
	catch (const out_of_range& e){
		cout << e.what() << endl;
		return false;
	}
	return true;
}

bool DungeonHandler::AddExpansion(long dungeon, Position& pos, Direction dir){
	try{
		auto exp = Expansion(pos, dir);
		dungeons.at(dungeon)->AddExpansion(exp);
	}
	catch (const out_of_range& e){
		cout << e.what() << endl;
		return false;
	}
	return true;
}

bool DungeonHandler::Generate(long dungeon){
	try{
		dungeons.at(dungeon)->Generate();
	}
	catch (const out_of_range& e){
		cout << e.what() << endl;
		return false;
	}
	return true;
}

unique_ptr<Tile> DungeonHandler::GetTiles(long dungeon){
	unique_ptr<Tile> tile = nullptr;

	try{
		tile = dungeons.at(dungeon)->GetTiles();
	}
	catch (const out_of_range& e){
		cout << e.what() << endl;
		return nullptr;
	}
	return tile;
}
