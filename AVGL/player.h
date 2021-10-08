#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "gameTile.h"

class Player
{
private:
	// [HU] Jatekos alak
	sf::Sprite sprite; // [EN] contains player position
	sf::Texture texture;
	float movementSpeed;
	float* deltaTime;
	bool* moves;	// [EN] moves[0] = left
					//		moves[1] = right
					//		moves[2] = top
					//		moves[3] = down

	// [EN] Private functions
	void initializeVariables();
	void initializeTexture();
	void initializeSprite();

public:
	// [EN] Constructor, Destructor
	Player(float* deltaTime, float x = 100.f, float y = 100.f);
	virtual ~Player();

	// [EN] Functions
	void update(sf::RenderTarget* target, std::vector<std::vector<GameTile*>> &tiles);
	void updateInput(std::vector<std::vector<GameTile*>> &tiles);
	void updateWindowBoundsCollision(sf::RenderTarget* target);
	void updateWallCollison(sf::RenderTarget* target, std::vector<std::vector<GameTile *>> tiles);
	void render(sf::RenderTarget* target);

	// [EN] Getter, Setter
	sf::Vector2f getPosition() const;
	bool setPosition(const sf::Vector2f newPosition);
};

#endif 