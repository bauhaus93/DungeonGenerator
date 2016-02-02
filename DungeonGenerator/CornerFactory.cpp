#include "CornerFactory.h"

using namespace std;

CornerFactory::CornerFactory(const std::string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{

}


CornerFactory::~CornerFactory(){
}

unique_ptr<Tile> CornerFactory::Create(Expansion& exp){
	//Rotation will be defined later by expansions
	return make_unique<TileCorner>(id, exp, size);

}
