#include "player.h"

// [EN] Private functions
void Player::initializeVariables()
{
	this->movementSpeed = 200.f;
	this->moves = new bool[4];
}

void Player::initializeTexture()
{
	if (!this->texture.loadFromFile("C:/Egyetem/Allamvizsga/images/mouse.png"))
	{
		std::cout << "Error::Player::initializeTexture::Could not load texture file." << std::endl;
	}
}

void Player::initializeSprite()
{
	this->sprite.setTexture(this->texture);
}


// [EN] Constructor, Destructor
Player::Player(float* dt, float x, float y)
{
	this->deltaTime = dt;
	this->initializeTexture();
	this->initializeSprite();
	this->sprite.setPosition(x, y);
	this->initializeVariables();
}

Player::~Player()
{
	delete this->moves;
}


// [EN] Functions
void Player::update(sf::RenderTarget* target, std::vector<std::vector<GameTile *>> &tiles)
{
	// [EN] Keyboard input (funciton call)
	this->updateInput(tiles);
	
	// [EN] Window bound collision
	this->updateWindowBoundsCollision(target);

	// [EN] Wall collision
	this->updateWallCollison(target, tiles);
}

/*
void Player::updateInput(std::vector<std::vector<GameTile*>> &tiles)
{
	
	sf::Vector2i playerPos = sf::Vector2i(sprite.getPosition());
	//std::cout << "Player: x = " << playerPos.x << " y = " << playerPos.y << "\t";
	sf::Vector2i tilePos = sf::Vector2i(playerPos.y / TILE_SIZE, playerPos.x / TILE_SIZE);
	//std::cout << "Tile: i = " << tilePos.x << " j = " << tilePos.y << "\t\t";
	

	// [EN] Keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sf::Vector2f playerPos = sf::Vector2f(sprite.getPosition());
		sf::Vector2i tilePos = sf::Vector2i((playerPos.y - movementSpeed) / TILE_SIZE, playerPos.x / TILE_SIZE);

		if (tiles[tilePos.x][tilePos.y]->getTileType() == GameTile::PASSABLE)
		{
			sprite.move(-movementSpeed, 0.f);
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sf::Vector2f playerPos = sf::Vector2f(sprite.getPosition());
		sf::Vector2i tilePos = sf::Vector2i((playerPos.y + movementSpeed) / TILE_SIZE, playerPos.x / TILE_SIZE);

		if (tiles[tilePos.x][tilePos.y]->getTileType() == GameTile::PASSABLE)
		{
			sprite.move(movementSpeed, 0.f);
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		sf::Vector2i playerPos = sf::Vector2i(sprite.getPosition());
		sf::Vector2i tilePos = sf::Vector2i(playerPos.y / TILE_SIZE, (int)((playerPos.x - movementSpeed) / TILE_SIZE));

		std::cout << tilePos.x << " " << (int)((sprite.getPosition().x - movementSpeed) / TILE_SIZE) << std::endl;
		//if (tiles[tilePos.x][tilePos.y]->getTileType() == GameTile::PASSABLE)
		{
			sprite.move(0.f, -movementSpeed);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		sprite.move(0.f, movementSpeed);
	}
	
}
*/



void Player::updateInput(std::vector<std::vector<GameTile*>>& tiles)
{
	// [EN] Keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && moves[0])
	{
		sprite.move(-movementSpeed * deltaTime[0] , 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && moves[1])
	{
		sprite.move(movementSpeed * deltaTime[0], 0.f);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && moves[2])
	{
		sprite.move(0.f, -movementSpeed * deltaTime[0]);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && moves[3])
	{
		sprite.move(0.f, movementSpeed * deltaTime[0]);
	}	
}

void Player::updateWindowBoundsCollision(sf::RenderTarget* target)
{
	// [HU] Megszabjuk, hogy a jatekos kilepjen a fo ablakbol
	// [EN] Left
	if (this->sprite.getGlobalBounds().left <= 0.f)
	{
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
	}
	// [EN] Right
	if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x)
	{
		this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
	}
	// [EN] Top
	if (this->sprite.getGlobalBounds().top <= 0.f)
	{
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
	}
	// [EN] Bottom
	if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y)
	{
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);
	}
}

void Player::updateWallCollison(sf::RenderTarget* target, std::vector<std::vector<GameTile*>> tiles)
{
	// [HU]	Egyszeruseg kedveert [i,j] koordinatak annak a 'kockanak' az indexjei amelyiken van a jatekosunk
	int i = sprite.getPosition().y / TILE_SIZE;
	int j = sprite.getPosition().x / TILE_SIZE;
	sf::Vector2f spriteTopRight = sf::Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width, sprite.getPosition().y);
	sf::Vector2f spriteBotLeft = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + sprite.getGlobalBounds().height);
	sf::Vector2f spriteBotRight = sf::Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width,
												sprite.getPosition().y + sprite.getGlobalBounds().height);

	// [HU] A kovetkezo lepesek mindegyik iranyra vonatkozik
	// [EN] LEFT
	if (j - 1 >= 0)
	{
		// [HU] Ha a bal felere nem lephetunk
		if (tiles[i][j - 1]->getTileType() == GameTile::UNPASSABLE // [HU] S kell, hogy erzekelje a bal also sarka is
			|| tiles[(int)((sprite.getPosition().y + sprite.getGlobalBounds().height) / TILE_SIZE)][j - 1]->getTileType() == GameTile::UNPASSABLE
			)
		{
			// [HU]	Ha egy balra lepessel belepnenk a falba
			//		akkor inkabb elmejunk a fal melle
			//		es letiltjuk, hogy mehessunk meg balra.
			if (j != (int)((sprite.getGlobalBounds().left - this->movementSpeed * this->deltaTime[0]) / TILE_SIZE))
			{
				this->moves[0] = false;

				// [HU] atveszem a key inputot es itt kezelem tovabba
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					std::cout << "Falnak ment. [LEFT]" << std::endl;
					sprite.setPosition(j * TILE_SIZE, sprite.getGlobalBounds().top);
				}
			}
			else this->moves[0] = true;
		}
		else this->moves[0] = true;
	}
	else this->moves[0] = true;

	// [EN] RIGHT
	if (j + 1 < tiles[0].size())
	{
		if (tiles[i][j + 1]->getTileType() == GameTile::UNPASSABLE
			//|| tiles[(int)((sprite.getPosition().y + sprite.getGlobalBounds().height) / TILE_SIZE)][(int)((sprite.getPosition().x + sprite.getGlobalBounds().width) / TILE_SIZE)]->getTileType() == GameTile::UNPASSABLE
			)
		{
			if (j != (int)((sprite.getGlobalBounds().left + sprite.getGlobalBounds().width + movementSpeed * deltaTime[0]) / TILE_SIZE) )
			{
				this->moves[1] = false;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					std::cout << "Falnak ment. [RIGHT]" << std::endl;
					sprite.setPosition(j * TILE_SIZE, sprite.getGlobalBounds().top);
				}
			}
			else this->moves[1] = true;
		}
		else this->moves[1] = true;
	}
	else this->moves[1] = true;

	// [EN] UP
	if (i - 1 >= 0)
	{
		if (tiles[i - 1][j]->getTileType() == GameTile::UNPASSABLE)
		{
			if (i != (int)((sprite.getGlobalBounds().top - this->movementSpeed * this->deltaTime[0]) / TILE_SIZE))
			{
				this->moves[2] = false;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					std::cout << "Falnak ment. [UP]" << std::endl;
					sprite.setPosition(sprite.getGlobalBounds().left, i * TILE_SIZE);
				}
			}
			else this->moves[2] = true;
		}
		else this->moves[2] = true;
	}
	else this->moves[2] = true;

	// [EN] DOWN
	if (i + 1 < tiles.size())
	{
		if (tiles[i + 1][j]->getTileType() == GameTile::UNPASSABLE)
		{
			if (i != (int)((sprite.getGlobalBounds().top + sprite.getGlobalBounds().height + movementSpeed * deltaTime[0]) / TILE_SIZE))
			{
				this->moves[3] = false;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					std::cout << "Falnak ment. [DOWN]" << std::endl;
					sprite.setPosition(sprite.getGlobalBounds().left, i * TILE_SIZE);
				}
			}
			else this->moves[3] = true;
		}
		else this->moves[3] = true;
	}
	else this->moves[3] = true;
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}


// [EN] Getter, Setter
sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

bool Player::setPosition(const sf::Vector2f newPosition)
{
	this->sprite.setPosition(newPosition);
	return true; // [HU] ezen meg van amit dolgozni / nem vegleges
}

