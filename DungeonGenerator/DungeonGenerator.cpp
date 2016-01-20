#include "DungeonGenerator.h"

//TODO: if straight hall would be endcap, maybe make corner??

using namespace std;

static chrono::high_resolution_clock timer;


DungeonGenerator::DungeonGenerator():
	communicator{},
	maxSize{200},
	generator{ static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count())}{
}

DungeonGenerator::~DungeonGenerator(){
	if (communicator.Connected())
		communicator.Disconnect();
}

int DungeonGenerator::Random(int max){
	return generator() % max;
}

int DungeonGenerator::Random(int min, int max){
	return min + Random(max - min + 1);
}

void DungeonGenerator::Work(){
	string data;

	if (!communicator.Connect())
		return;

	data = communicator.ReadString();
	if (data == "START"){
		cout << "got a dungeon request" << endl;
	}
	else{
		cerr << "protocol error" << endl;
		communicator.Disconnect();
		return;
	}

	scale = communicator.ReadShort();
	if (scale <= 0){
		cerr << "invalid scale: " << scale << endl;
		communicator.Disconnect();
		return;
	}
	cout << "scale is " << scale << endl;

	do{
		data = communicator.ReadString();
		if (data != "END"){
			float x, y, z;
			x = communicator.ReadFloat();
			y = communicator.ReadFloat();
			z = communicator.ReadFloat();
			cout << "object: " << data << ": (" << x << "/" << y << "/" << z << ")" << endl;
			if (x == 0.f)
				tileIDs.insert(pair<TileType, string>(TileType::HALL1, data));
			else if (x == 512.f)
				tileIDs.insert(pair<TileType, string>(TileType::HALL2, data));
			else if (x == 1024.f)
				tileIDs.insert(pair<TileType, string>(TileType::HALL3, data));
			else if (x == 1536.f)
				tileIDs.insert(pair<TileType, string>(TileType::HALL4, data));
			else if (x == 2048.f)
				tileIDs.insert(pair<TileType, string>(TileType::CORNER, data));
			
		}
	} while (data != "END");

	cout << "request data finished" << endl;

	Position pos{ 0.f, 0.f, 0.f };
	Generate(pos, Direction::WEST);

	WriteTiles();

	/*for (auto& t : tiles){
		cout << t.GetString() << endl;
	}*/
	
	communicator.Disconnect();
}

void DungeonGenerator::WriteTiles(){
	cout << "sending tiles to morrowind..." << endl;
	for (auto& tile : tiles){
		if (communicator.HasError())
			break;
		communicator.WriteTile(tile);
	}
	cout << "all tiles sent to morrowind" << endl;
}

void DungeonGenerator::Generate(Position& pos, Direction dir){

	if (tiles.size() >= maxSize)
		return;

	if (!FreeSpace(pos, dir, 1)){
		MakeHallway1(pos, dir);
		cout << "no move possible in current dir!" << endl;
		return;
	}

	int rnd = Random(100);
	if (rnd < 10){
		int len = Random(1, 2);
		if (tiles.size() + len > maxSize){
			len = maxSize - tiles.size();
		}
		len = FreeSpace(pos, dir, len);
		MakeHallway2(pos, dir, len);
	}
	/*else if (rnd < 70){
		MakeHallway3(pos, dir);
	}*/
	else{
		MakeCorner(pos, dir);
	}
}

void DungeonGenerator::MakeHallway1(Position& pos, Direction dir){
	float zRot;

	switch (dir){
	case Direction::NORTH:
		zRot = 180.f;
		break;
	case Direction::EAST:
		zRot = 270.f;
		break;
	case Direction::SOUTH:
		zRot = 0.f;
		break;
	case Direction::WEST:
		zRot = 90.f;
		break;
	default:
		break;
	}
	tiles.push_back(Tile(tileIDs.at(TileType::HALL1), pos, zRot));
}

void DungeonGenerator::MakeHallway2(Position& pos, Direction dir, int length){
	float zRot;

	if (length == 0)
		return;

	switch (dir){
		case Direction::NORTH:
		case Direction::SOUTH:
			zRot = 0;
			break;
		case Direction::EAST:
		case Direction::WEST:
			zRot = 90;
			break;
		default:
			break;
	}

	for (int i = 0; i < length; i++){
		tiles.push_back(Tile(tileIDs.at(TileType::HALL2), pos, zRot));
		pos.Move(dir, scale);
	}
	Generate(pos, dir);
}

void DungeonGenerator::MakeHallway3(Position& pos, Direction dir){

}

void DungeonGenerator::MakeCorner(Position& pos, Direction& dir){
	bool endcap = false;
	float zRot = 0.f;

	switch (dir){
		case Direction::NORTH:
		case Direction::SOUTH:
			cout << "new corner from n/s" << endl;
			endcap = !CalculateCorner(pos, dir, Direction::EAST, Direction::WEST, zRot);
			break;
		case Direction::EAST:
		case Direction::WEST:
			cout << "new corner from e/w" << endl;
			endcap = !CalculateCorner(pos, dir, Direction::NORTH, Direction::SOUTH, zRot);
			break;
		default:
			break;
	}
	if (!endcap){
		tiles.push_back(Tile(tileIDs.at(TileType::CORNER), pos, zRot));
		pos.Move(dir, scale);
		Generate(pos, dir);
	}
}

bool DungeonGenerator::CalculateCorner(Position& pos, Direction& dir, Direction toA, Direction toB, float& zRot){
	Direction newDir;
	bool possible[] = { CornerPossible(pos, toA), CornerPossible(pos, toB) };

	if (possible[0] && possible[1]){
		cout << "both possible" << endl;
		if (Random(2) == 0)
			newDir = toA;
		else
			newDir = toB;
	}
	else if (possible[0]){
		cout << "to n/e possible" << endl;
		newDir = toA;
	}
	else if (possible[1]){
		cout << "to s/w possible" << endl;
		newDir = toB;
	}
	else{
		cout << "no possible corner" << endl;
		MakeHallway1(pos, dir);
		return false;
	}

	if (dir == Direction::NORTH && newDir == Direction::WEST || dir == Direction::EAST && newDir == Direction::SOUTH)
		zRot = 0.f;
	else if (dir == Direction::SOUTH && newDir == Direction::WEST || dir == Direction::EAST && newDir == Direction::NORTH)
		zRot = 90.f;
	else if (dir == Direction::SOUTH && newDir == Direction::EAST || dir == Direction::WEST && newDir == Direction::NORTH)
		zRot = 180.f;
	else if (dir == Direction::NORTH && newDir == Direction::EAST || dir == Direction::WEST && newDir == Direction::SOUTH)
		zRot = 270.f;
	dir = newDir;
	return true;
}

bool DungeonGenerator::WouldCollide(const Position& pos){
	for (auto& tile : tiles){
		const Position& tilePos = tile.GetPos();
		if (abs(pos.GetX() - tilePos.GetX()) < scale  && abs(pos.GetY() - tilePos.GetY()) < scale)
			return true;
	}
	return false;
}

int DungeonGenerator::FreeSpace(Position pos, Direction dir, int times){

	for (int i = 0; i < times; i++){
		pos.Move(dir, scale);
		if (WouldCollide(pos))
			return i;
	}
	return times;
}

bool DungeonGenerator::CornerPossible(Position pos, Direction newDir){
	pos.Move(newDir, scale);
	return !WouldCollide(pos);
}


