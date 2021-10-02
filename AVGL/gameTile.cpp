#include "gameTile.h"

void GameTile::initializeSprite(std::string)
{
	this->sprite.setTexture(this->texture);
}

void GameTile::initializeTexture(std::string)
{
	if (!this->texture.loadFromFile("C:/Egyetem/Allamvizsga/images/wall.png"))
	{
		std::cout << "Error::GameTile::initializeTexture::Could not load texture file." << std::endl;
	}
}

// [EN] Constructor, Destructor
GameTile::GameTile(std::string textureName, float x, float y, int gameTileType)
{	
	initializeSprite(textureName);
	pos = sf::Vector2f(x, y);
	sprite.setPosition(pos);
	gameTileType = gameTileType;
}

GameTile::~GameTile()
{
}

// [EN] Functions
void GameTile::update(sf::RenderTarget* target)
{
	// [HU] Ha az eger ralep a talajra
}

void GameTile::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
