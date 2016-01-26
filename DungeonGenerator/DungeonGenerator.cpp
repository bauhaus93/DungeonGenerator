#include "DungeonGenerator.h"

//TODO: if straight hall would be endcap, maybe make corner??

using namespace std;

static chrono::high_resolution_clock timer;


DungeonGenerator::DungeonGenerator():
	communicator{},
	maxSize{300}{

	common::Randomize();
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

		vector<Expansion> possibleExpansions;
		GetPossibleExpansions(*exp, factory[TileType::HALL1]->GetSize(), possibleExpansions);

		auto& tf = GetFactory(exp->GetDirection(), possibleExpansions);
		
		auto tile = tf.Create(*exp);
		if (tile != NULL){
			tile->AddValidExpansions(*exp, expansions, possibleExpansions);
			tiles.push_back(move(tile));
		}
	}

	chrono::duration<float> diff = (timer.now() - start);
	cout << std::setprecision(2) << std::fixed << "dungeon created in " << diff.count()*1e3 << " ms" << endl;
}

TileFactory& DungeonGenerator::GetFactory(Direction currDir, vector<Expansion>& possibleExpansions){
	if (tiles.size() + 1 == maxSize || possibleExpansions.size() == 0)
		return *factory[TileType::HALL1];

	bool straight = false;
	for (auto& exp : possibleExpansions){
		if (currDir == exp.GetDirection())
			straight = true;
	}

	if (common::Random(4) == 0 || straight == false)
		return *factory[TileType::CORNER];

	return *factory[TileType::HALL2];
}

void DungeonGenerator::GetPossibleExpansions(const Expansion& src, const Size& size, vector<Expansion>& possibleExpansions){
	Expansion test = src;

	for (int i = 0; i < 4; i++){
		auto dir = static_cast<Direction>(i);
		test.Move(dir, size);
		if (collision->Check(test, size) == false){
			possibleExpansions.push_back(test);
			possibleExpansions.back().SetDirection(dir);
		}
		test.Move(common::OppositeDirection(dir), size);
	}
}