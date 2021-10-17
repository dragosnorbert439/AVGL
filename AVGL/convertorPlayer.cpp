#pragma once
#include <utility>

std::pair<unsigned int, unsigned int> posToTile(float &posX, float &posY, int &tileSize)
{
	return { (unsigned int)(posY / tileSize), (unsigned int)(posX / tileSize) };
}