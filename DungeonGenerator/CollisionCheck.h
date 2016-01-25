#pragma once

#include <vector>
#include <memory>

#include "Tile.h"
#include "Expansion.h"
#include "Position.h"

bool CheckCollision(const Position& pos, const Size& size, const std::vector<Tile>& tiles, const std::vector<std::unique_ptr<Expansion>>& expansions);
static bool CheckCoordinate(float dimA, float sizeA, float dimB, float sizeB);

