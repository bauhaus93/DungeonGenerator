#include "CornerFactory.h"



CornerFactory::CornerFactory(const std::string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{

}


CornerFactory::~CornerFactory(){
}

bool CornerFactory::Add(std::vector<Tile>& tiles, std::vector<std::unique_ptr<Expansion>>& expansions){
	return false;
}
