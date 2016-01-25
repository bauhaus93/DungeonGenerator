#include "CornerFactory.h"

using namespace std;

CornerFactory::CornerFactory(const std::string& idArg, const Size& sizeArg):
	TileFactory{ idArg, sizeArg }{

}


CornerFactory::~CornerFactory(){
}

unique_ptr<Tile> CornerFactory::Create(Expansion& exp){
	Rotation rot{};

	switch (exp.GetDirection()){
	case Direction::NORTH:
	case Direction::EAST:
		rot[Dim::Z] = 0.f;
		break;
	case Direction::SOUTH:
	case Direction::WEST:
		rot[Dim::Z] = 90.f;
		break;
	default:
		return NULL;
		break;
	}
	return make_unique<TileCorner>(id, exp, size, rot);

}
