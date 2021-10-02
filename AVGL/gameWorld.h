#include <SFML/Graphics.hpp>
#include "gameTile.h"
#include "mouse.h"
#include <vector>

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld
{
	Mouse mouse;
	sf::Vector2i mousePosition;
	std::vector<sf::Vector2i> catPositions;
	void setUpInitialState();
	void setUpEnemyPosition();
	void setUpTiles();

public:
	std::vector< std::vector<GameTile*>> tiles;
	int gridLength;

	GameWorld();
	void update();
	sf::Vector2i getMousePosition() const { return mousePosition; };

};

#endif
