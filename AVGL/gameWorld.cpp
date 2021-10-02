#include "gameWorld.h"

GameWorld::GameWorld()
{
	gridLength = 8;
	setUpInitialState();
}

void GameWorld::setUpInitialState()
{
	mousePosition = sf::Vector2i(1, 1);
	setUpTiles();
	setUpEnemyPosition();
	
}

void GameWorld::setUpEnemyPosition()
{
	catPositions.clear();
	catPositions.push_back(sf::Vector2i(5, 5));
	catPositions.push_back(sf::Vector2i(1, 6));
	catPositions.push_back(sf::Vector2i(6, 1));
}

void GameWorld::setUpTiles()
{
	tiles.clear();
	std::vector<GameTile*> row;
	for (int i = 0; i < gridLength; ++i)
	{
		row.clear();
		for (int j = 0; j < gridLength; ++j)
		{
			if (i == 0 || j == 0 || i == gridLength - 1 || j == gridLength - 1) row.push_back(new GameTile("C:/Egyetem/Allamvizsga/images/wall.png", j * 50, i * 50, false));
			else row.push_back(new GameTile("C:/Egyetem/Allamvizsga/images/ground.png", j * 50, i * 50, true));
		}
		tiles.push_back(row);
	}
}

void GameWorld::update()
{
	mouse.updateMouse();
}