#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

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
	float dt{ 1 };	// [HU] Delta ido, hogy gyors gepen is ugy fusson,
					//      mind egy lassun es forditva

	std::vector<std::vector<GameTile *>> tiles;

	bool gameOver;
	int gameRows { 8 };
	int gameCols { 8 };

	// [EN] Window
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;

	// [EN] Private functions
	void initializeVariables();
	void initializeWindow();
	void initializePlayer();
	void initializeTiles();

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
	void setDeltaTime(const float value);
	float getDeltaTime() const;
};

#endif
