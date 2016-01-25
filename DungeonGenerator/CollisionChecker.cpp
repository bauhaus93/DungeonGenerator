#include "CollisionChecker.h"

using namespace std;

CollisionChecker::CollisionChecker(const vector<unique_ptr<Tile>>& tilesArg, const vector<unique_ptr<Expansion>>& expansionsArg) :
	tiles{ tilesArg },
	expansions{ expansionsArg }{
}

CollisionChecker::~CollisionChecker(){

}

bool CollisionChecker::Check(const Position& pos, const Size& size){

	for (const auto& tile : tiles){
		bool collides = true;

		for (int dim = 0; collides && dim < 3; dim++){
			collides &= CheckCoordinate(pos[static_cast<Dim>(dim)], size[static_cast<Dim>(dim)], tile->GetPos()[static_cast<Dim>(dim)], tile->GetSize()[static_cast<Dim>(dim)]);
		}
		if (collides)
			return true;
	}
	for (const auto& exp : expansions){
		bool collides = true;

		for (int dim = 0; collides && dim < 3; dim++){
			collides &= CheckCoordinate(pos[static_cast<Dim>(dim)], size[static_cast<Dim>(dim)], (*exp)[static_cast<Dim>(dim)], (*exp)[static_cast<Dim>(dim)]);
		}
		if (collides)
			return true;
	}
	return false;
}


