#include "CollisionCheck.h"

using namespace std;

bool CheckCollision(const Position& pos, const Size& size, const vector<Tile>& tiles, const vector<unique_ptr<Expansion>>& expansions){

	for (auto& tile : tiles){
		for (int dim = 0; dim < 3; dim++){
			if (CheckCoordinate(pos[static_cast<Dim>(dim)], size[static_cast<Dim>(dim)], tile.GetPos()[static_cast<Dim>(dim)], tile.GetSize()[static_cast<Dim>(dim)]))
				return true;
		}
	}
	return false;
}

static bool CheckCoordinate(float dimA, float sizeA, float dimB, float sizeB){
	if (abs(dimA - dimB) < ((sizeA / 2) + (sizeB / 2)))
		return true;
	return false;
}


