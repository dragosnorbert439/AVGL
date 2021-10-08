#include "gameTile.h"


void GameTile::initializeTexture(std::string textureName)
{
	if (!this->texture.loadFromFile(textureName))
	{
		std::cout << "Error::GameTile::initializeTexture::Could not load texture file." << std::endl;
	}
}

void GameTile::initializeSprite()
{
	this->sprite.setTexture(this->texture);
}

// [EN] Constructor, Destructor
GameTile::GameTile(std::string textureName, float x, float y, int tileType)
{	
	initializeTexture(textureName);
	initializeSprite();
	this->sprite.setPosition(x, y);
	this->gameTileType = tileType;
}

GameTile::~GameTile()
{
}

// [EN] Functions
void GameTile::update(sf::RenderTarget* target)
{
	// [HU] Ha az eger ralep a talajra - meg kell dolgozni rajta
}

void GameTile::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

// [EN] Getter
int GameTile::getTileType() const
{
	return this->gameTileType;
}

sf::Vector2f GameTile::getPosition() const
{
	return this->pos;
}

