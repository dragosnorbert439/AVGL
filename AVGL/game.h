#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <vector>

#include "player.h"
#include "gameTile.h"

/*
	[HU] Ez az osztaly fog megoldani nagyjabol mindent
*/

class Game
{
private:
	// [EN] Variables
	Player *player;
	bool gameOver;
	std::vector<std::vector<GameTile*>> tiles;

	// [EN] Window
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;

	// [EN] Private functions
	void initializeVariables();
	void initializeWindow();
	void initializePlayer();
	void initializeMap();

public:
	// [EN] Constructor, Destructor
	Game();
	virtual ~Game();

	// [EN] Accessors
	const bool isRunning() const;

	// [EN] Functions
	void update();
	void render();
	void pollEvents();
};

#endif
