#include "DungeonGenerator.h"

//TODO: if straight hall would be endcap, maybe make corner??

using namespace std;

static chrono::high_resolution_clock timer;


DungeonGenerator::DungeonGenerator():
	communicator{},
	/*collision{ tiles, expansions },*/
	maxSize{300},
	generator{ static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count())}{

	collision = make_unique<CollisionChecker>(tiles, expansions);
}

DungeonGenerator::~DungeonGenerator(){
	communicator.Disconnect();
}

void DungeonGenerator::Work(){
	string data;
	short scale = 0;

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
				factory.insert(make_pair(TileType::HALL1, make_unique<Hallway1Factory>(data, Size(scale, scale, scale))));
			else if (x == 512.f)
				factory.insert(make_pair(TileType::HALL2, make_unique<Hallway2Factory>(data, Size(scale, scale, scale))));
			else if (x == 2048.f)
				factory.insert(make_pair(TileType::CORNER, make_unique<CornerFactory>(data, Size(scale, scale, scale))));
		}
	} while (data != "END");

	cout << "request data finished" << endl;

	AddExpansion(Expansion(0.f, 0.f, 0.f, Direction::NORTH));
	Generate();
	WriteTiles();

	communicator.Disconnect();
}

void DungeonGenerator::WriteTiles(){
	size_t count = 0;
	auto start = timer.now();

	cout << "sending tiles..." << endl;
	for (const auto& tile : tiles){
		if (communicator.HasError())
			break;
		communicator.WriteTile(*tile);
		count++;
	}
	chrono::duration<float> diff = (timer.now() - start);

	cout << "sent " << count << " tiles in " << std::setprecision(2) << std::fixed << diff.count()*1e3 << " ms" << endl;
}

void DungeonGenerator::AddExpansion(const Expansion& exp){
	expansions.push_back(make_unique<Expansion>(exp));
}

void DungeonGenerator::Generate(){
	cout << "creating dungeon..." << endl;

	auto start = timer.now();

	while (tiles.size() < maxSize && !expansions.empty()){
		auto exp = move(expansions.back());
		expansions.pop_back();

		auto& tf = GetFactory();

		if (collision->Check(*exp, tf.GetSize()))
			continue;
		
		auto tile = tf.Create(*exp);
		if (tile != NULL){
			tile->AddExpansions(*exp, expansions);
			tiles.push_back(move(tile));
		}
	}
	chrono::duration<float> diff = (timer.now() - start);

	cout << std::setprecision(2) << std::fixed << "dungeon created in " << diff.count()*1e3 << " ms" << endl;
}

TileFactory& DungeonGenerator::GetFactory(){
	if (tiles.size() + 1 == maxSize)
		return *factory[TileType::HALL1];
	return *factory[TileType::HALL2];
}

/*void DungeonGenerator::MakeCorner(Position& pos, Direction& dir){
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

*/
