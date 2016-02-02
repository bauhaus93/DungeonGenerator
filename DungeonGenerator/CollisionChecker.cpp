#include "CollisionChecker.h"

using namespace std;

CollisionChecker::CollisionChecker(const vector<unique_ptr<Tile>>& tilesArg, const vector<unique_ptr<Expansion>>& expansionsArg):
	tiles{ tilesArg },
	expansions{ expansionsArg }{
}

CollisionChecker::~CollisionChecker(){

}

bool CollisionChecker::ValidateDungeon(){
	int collisions = 0;
	bool valid = true;

	auto start = common::Time();

	if (!expansions.empty()){
		cout << "Dungeon invalid : " << expansions.size() << " expansions left!" << endl;
		valid = false;
	}
	for (size_t i = 0; i < tiles.size(); i++){
		for (size_t j = 0; j < tiles.size(); j++){
			if (i != j){
				if (Collides(tiles[i]->GetPos(), tiles[i]->GetSize(), tiles[j]->GetPos(), tiles[j]->GetSize())){
					collisions++;
				}
			}
		}
	}
	if (collisions > 0){
		cout << "Dungeon invalid: " << collisions << " collisions detected!" << endl;
		valid = false;
	}
	if (valid)
		cout << "Dungeon valid!" << endl;

	auto diff = common::TimeDiff(start);
	cout << "Dungeon validation took " << diff*1e3 << "ms" << endl;

	return valid;

}

bool CollisionChecker::Check(const Position& pos, const Size& size){

	for (const auto& tile : tiles){
		if (Collides(pos, size, tile->GetPos(), tile->GetSize()))
			return true;
	
	}
	for (const auto& exp : expansions){
		if (Collides(pos, size, *exp, size))
			return true;
	}
	return false;
}

bool CollisionChecker::Recheck(){
	const Size size{ 512.f, 512.f, 512.f };

	for (size_t i = 0; i < expansions.size(); i++){
		for (size_t j = 0; j < expansions.size(); j++){
			if (i != j){
				if (Collides(*expansions[i], size, *expansions[j], size)){
					cout << "collision detected, skipping..." << endl;
					return true;
				}
			}
		}
	}
	return false;
}



bool CollisionChecker::Collides(const Position& posA, const Size& sizeA, const Position& posB, const Size& sizeB){
	bool collides = true;

	for (int dim = 0; collides && dim < 3; dim++){
		collides &= CheckCoordinate(posA[static_cast<Dim>(dim)], sizeA[static_cast<Dim>(dim)], posB[static_cast<Dim>(dim)], sizeB[static_cast<Dim>(dim)]);
	}
	return collides;
}