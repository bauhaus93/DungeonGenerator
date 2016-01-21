#include "Expansion.h"



Expansion::Expansion(float xArg, float yArg, float zArg, Direction dirArg):
	Position{ xArg, yArg, zArg },
	dir{ dirArg }{
}

Expansion::Expansion(const Position& pos, Direction dirArg):
	Position{ pos },
	dir{ dirArg }{
}

Expansion::~Expansion(){
}