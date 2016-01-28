#include "DungeonGenerator.h"

//TODO: if straight hall would be endcap, maybe make corner??

using namespace std;

static chrono::high_resolution_clock timer;


DungeonGenerator::DungeonGenerator():
	maxSize{300}{

	common::Randomize();
	collision = make_unique<CollisionChecker>(tiles, expansions);
	cout << "New Dungeon Generator created!" << endl;
}

DungeonGenerator::~DungeonGenerator(){

}

void DungeonGenerator::AddTileFactory(TileType type, string id, Size& size){
	switch (type){
	case TileType::HALL1:
		factory.insert(make_pair(type, make_unique<Hallway1Factory>(id, size)));
		break;
	case TileType::HALL2:
		factory.insert(make_pair(type, make_unique<Hallway2Factory>(id, size)));
		break;
	/*case TileType::HALL3:
		factory.insert(make_pair(type, make_unique<Hallway3Factory>(id, size)));
		break;
	case TileType::HALL4:
		factory.insert(make_pair(type, make_unique<Hallway4Factory>(id, size)));
		break;*/
	case TileType::CORNER:
		factory.insert(make_pair(type, make_unique<CornerFactory>(id, size)));
		break;
	default:
		break;
	}
}

unique_ptr<Tile> DungeonGenerator::GetTiles(){
	if (tiles.empty())
		return nullptr;
	auto tile = move(tiles.back());
	tiles.pop_back();
	return move(tile);
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