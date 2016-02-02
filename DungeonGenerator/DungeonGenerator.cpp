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
		case TileType::HALL3:
			factory.insert(make_pair(type, make_unique<Hallway3Factory>(id, size)));
			break;
		/*case TileType::HALL4:
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
		auto exp = move(expansions.front());
		expansions.pop_back();

		cout << "gpe!" << endl;
		vector<Expansion> possibleExpansions;
		GetPossibleExpansions(*exp, factory[TileType::HALL1]->GetSize(), possibleExpansions);
		cout << "fin!" << endl;

		auto& tf = GetFactory(exp->GetDirection(), possibleExpansions);
		
		auto tile = tf.Create(*exp);
		if (tile != nullptr){
			tile->AddValidExpansions(*exp, expansions, possibleExpansions);
			tiles.push_back(move(tile));
		}
		cout << "run finished!" << endl;
	}

	chrono::duration<float> diff = (timer.now() - start);
	cout << std::setprecision(2) << std::fixed << "dungeon created in " << diff.count()*1e3 << " ms (" << tiles.size() << " tiles)" << endl;
}

TileFactory& DungeonGenerator::GetFactory(Direction currDir, vector<Expansion>& possibleExpansions){

	bool straightPossible = false;
	bool cornerPossible = false;
	bool threeWayPossible = possibleExpansions.size() == 3;
	bool fourWayPossible = possibleExpansions.size() == 4;

	for (auto& exp : possibleExpansions){
		if (currDir == exp.GetDirection())
			straightPossible = true;
		if (currDir != exp.GetDirection() && currDir != common::OppositeDirection(exp.GetDirection()))
			cornerPossible = true;
	}

	if (tiles.size() < maxSize){
		int rnd = common::Random(100);
		cout << "rnd: " << rnd << endl;

		if (fourWayPossible && rnd < 0){	//make 5
			return *factory[TileType::HALL3];	//TODO: Make 4way
		}
		else if (threeWayPossible && rnd < 10){
			return *factory[TileType::HALL3];
		}
		else if (rnd < 20){
			if (cornerPossible)
				return *factory[TileType::CORNER];
			else if(straightPossible)
				return *factory[TileType::HALL2];
			//else ENDCAP
		}
		else{
			if (straightPossible){
				return *factory[TileType::HALL2];
			}
			else if(cornerPossible)
				return *factory[TileType::CORNER];
			//else ENDCAP
		}
		//else ENDCAP
	}

	return *factory[TileType::HALL1];
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