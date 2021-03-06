#include "DungeonGenerator.h"

using namespace std;

DungeonGenerator::DungeonGenerator():
	maxSize{ 100 }{

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
		case TileType::HALL4:
			factory.insert(make_pair(type, make_unique<Hallway4Factory>(id, size)));
			break;
		case TileType::CORNER:
			factory.insert(make_pair(type, make_unique<CornerFactory>(id, size)));
			break;
		default:
			assert(0);
			break;
	}
}

unique_ptr<Tile> DungeonGenerator::GetTiles(){
	if (tiles.empty())
		return nullptr;
	auto tile = move(tiles.back());
	tiles.pop_back();

	/*if (tiles.size() % 1000 == 0){
		cout << "tiles left for retrieving: " << tiles.size() << endl;
	}*/

	return move(tile);
}

void DungeonGenerator::AddExpansion(const Expansion& exp){
	expansions.push_back(make_unique<Expansion>(exp));
}

void DungeonGenerator::Generate(){
	assert(factory.size() == 5);

	cout << "creating dungeon..." << endl;

	auto start = common::Time();

	MakeFirstTile();

	while (tiles.size() < maxSize && !expansions.empty()){
		/*if (tiles.size() % 1000 == 0){
			cout << "curr dungeon size: " << tiles.size() << endl;
		}*/
		//auto exp = move(expansions.back());
		//expansions.pop_back();	//if pop_back() must also use expansion.back() not .front()
		auto exp = move(expansions.front());
		expansions.erase(expansions.begin());

		vector<Expansion> possibleExpansions;
		GetPossibleExpansions(*exp, factory[TileType::HALL1]->GetSize(), possibleExpansions);

		auto& tf = GetFactory(exp->GetDirection(), possibleExpansions);
		
		auto tile = tf.Create(*exp);
		if (tile != nullptr){
			tile->AddValidExpansions(*exp, expansions, possibleExpansions);
			tiles.push_back(move(tile));
		}
	}

	FinishExpansions();

	auto diff = common::TimeDiff(start);
	cout << std::setprecision(2) << std::fixed << "dungeon created in " << diff << " (" << tiles.size() << " tiles)" << endl;

	collision->ValidateDungeon();
}

TileFactory& DungeonGenerator::GetFactory(Direction currDir, vector<Expansion>& possibleExpansions){

	bool straightPossible = false;
	bool cornerPossible = false;
	bool threeWayPossible = possibleExpansions.size() >= 2;
	bool fourWayPossible = possibleExpansions.size() >= 3;

	if (possibleExpansions.empty())
		return *factory[TileType::HALL1];

	for (auto& exp : possibleExpansions){
		if (currDir == exp.GetDirection())
			straightPossible = true;
		if (currDir != exp.GetDirection() && currDir != common::OppositeDirection(exp.GetDirection()))
			cornerPossible = true;
	}

	if (tiles.size() < maxSize){
		int rnd = common::Random(100);

		if (rnd < 5){
			return *factory[TileType::HALL1];
		}
		else if (fourWayPossible && rnd < 10){
			return *factory[TileType::HALL4];
		}
		else if (threeWayPossible && rnd < 15){
			return *factory[TileType::HALL3];
		}
		else if (rnd < 50){
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

void DungeonGenerator::MakeFirstTile(){
	assert(expansions.size() > 0);

	auto exp = move(expansions.back());
	expansions.pop_back();
	tiles.push_back(factory[TileType::HALL1]->Create(*exp));
	//exp->SetDirection(common::OppositeDirection(exp->GetDirection()));
	exp->Move(exp->GetDirection(), factory[TileType::HALL1]->GetSize());
	expansions.push_back(move(exp));
}

void DungeonGenerator::FinishExpansions(){
	vector<Expansion> dummy;
	while (!expansions.empty()){
		auto exp = move(expansions.back());
		expansions.pop_back();
		auto tile = factory[TileType::HALL1]->Create(*exp);
		if (tile != nullptr){
			tile->AddValidExpansions(*exp, expansions, dummy);
			tiles.push_back(move(tile));
		}
	}
}