#ifndef GAMETILE_H
#define GAMETILE_H

#include <iostream>

#include <SFML/Graphics.hpp>

#define TILE_SIZE 50

/*
	[HU] Otletek: ENUM a tile tipusra: PASSABLE UNPASSABLE meg egyeb
*/

class GameTile
{
private:
	sf::Vector2f pos;
	sf::Texture texture;
	sf::Sprite sprite;
	int gameTileType; // [EN] 0 = PASSABLE, 1 = UNPASSABLE

	// [EN] Private functions
	void initializeSprite(std::string textureName);
	void initializeTexture(std::string textureName);

public:
	// [EN] Constructor, Destructor
	GameTile(std::string textureName, float x, float y, int gameTileType);
	virtual ~GameTile();

	// [EN] Enums
	typedef enum { PASSABLE, UNPASSABLE };

	// [EN] Functions
	void update(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

#endif