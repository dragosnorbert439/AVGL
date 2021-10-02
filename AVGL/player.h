#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	// [HU] Jatekos alak
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	float movementSpeed;

	// [EN] Private functions
	void initializeVariables();
	void initializeTexture();
	void initializeSprite();

public:
	// [EN] Constructor, Destructor
	Player(float x = 50.f, float y = 50.f);
	virtual ~Player();

	// [EN] Functions
	void update(const sf::RenderTarget* target);
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

	// [EN] Getter, Setter
	sf::Vector2f getPosition() const;
	bool setPosition(const sf::Vector2f newPosition);
};

#endif 