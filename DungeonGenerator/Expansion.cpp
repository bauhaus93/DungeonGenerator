#include "Expansion.h"



Expansion::Expansion(float x, float y, float z, Direction dirArg):
	Position{ x, y, z },
	dir{ dirArg }{
}

Expansion::Expansion(const Position& pos, Direction dirArg):
	Position{ pos },
	dir{ dirArg }{
}

Expansion::~Expansion(){
}