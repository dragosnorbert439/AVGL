#include "player.h"
#define eps 2
#define MS 175UL

// [EN] Private functions
void Player::initializeVariables()
{
	this->movementSpeed = 20.f;
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
Player::Player(float x, float y)
{
	this->initializeTexture();
	this->initializeSprite();
	this->sprite.setPosition(x, y);
	this->initializeVariables();
}

Player::~Player()
{
	delete this->moves;
}


// [EN] Game class related functions (initializers)
void Player::setDT(float* gameDeltaTime)
{
	this->deltaTime = gameDeltaTime;
}

void Player::setGameRenderWindow(sf::RenderWindow** gameRenderWindow)
{
	this->gameRenderWindow = gameRenderWindow;
}

void Player::setGameEvent(sf::Event* gameEvent)
{
	this->gameEvent = gameEvent;
}


// [EN] Functions
void Player::update(sf::RenderTarget* target, std::vector<std::vector<GameTile *>> &tiles)
{
	// [EN] Wall collision
	this->updateWallCollison(target, tiles);

	// [EN] Keyboard input (funciton call)
	this->updateInput(tiles);
	
	// [EN] Window bound collision
	this->updateWindowBoundsCollision(target);

}

void Player::updateInput(std::vector<std::vector<GameTile*>>& tiles)
{
	// [EN] Keyboard input
	// [EN] LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && moves[0])
	{
		sprite.move(-TILE_SIZE, 0.f);
		std::this_thread::sleep_for(std::chrono::milliseconds(MS));
		return;
	}
	// [EN] RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && moves[1])
	{
		sprite.move(TILE_SIZE, 0.f);
		std::this_thread::sleep_for(std::chrono::milliseconds(MS));
		return;
	}
	// [EN] UP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && moves[2])
	{
		sprite.move(0.f, -TILE_SIZE);
		std::this_thread::sleep_for(std::chrono::milliseconds(MS));
		return;
	}
	// [EN] DOWN
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && moves[3])
	{
		sprite.move(0.f, TILE_SIZE);
		std::this_thread::sleep_for(std::chrono::milliseconds(MS));
		return;
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
	/*
	* [EN] Variables used to help understand:
	*	 // [HU]	Egyszeruseg kedveert [i,j] koordinatak annak a 'kockanak' az indexjei amelyiken van a jatekosunk
		
		sf::Vector2f spriteTopRight = sf::Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width, sprite.getPosition().y);
		sf::Vector2f spriteBotLeft = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + sprite.getGlobalBounds().height);
		sf::Vector2f spriteBotRight = sf::Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width,
													sprite.getPosition().y + sprite.getGlobalBounds().height);
	*/
	//std::cout << sprite.getPosition().y + sprite.getGlobalBounds().height << " " << sprite.getPosition().x << std::endl;

	int i = sprite.getPosition().y / TILE_SIZE;
	int j = sprite.getPosition().x / TILE_SIZE;

	// [HU] A kovetkezo lepesek mindegyik iranyra vonatkozik
	// [EN] LEFT
	if (j - 1 >= 0)
	{
		// [HU] Ha a bal felere nem lephetunk
		if (tiles[i][j - 1]->getTileType() == GameTile::UNPASSABLE)
		{
			this->moves[0] = false;
		}
		else this->moves[0] = true;
	}
	else this->moves[0] = true;

	// [EN] RIGHT
	if (j + 1 < tiles[0].size())
	{
		if (tiles[i][j + 1]->getTileType() == GameTile::UNPASSABLE)
		{
			this->moves[1] = false;
		}
		else this->moves[1] = true;
	}
	else this->moves[1] = true;

	// [EN] UP
	if (i - 1 >= 0)
	{
		if (tiles[i - 1][j]->getTileType() == GameTile::UNPASSABLE)
		{
			this->moves[2] = false;
		}
		else this->moves[2] = true;
	}
	else this->moves[2] = true;

	// [EN] DOWN
	if (i + 1 < tiles.size())
	{
		if (tiles[i + 1][j]->getTileType() == GameTile::UNPASSABLE)
		{
			this->moves[3] = false;
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
	return this->sprite.getPosition(); // [HU] ez lehet folosleges
}

bool Player::setPosition(const sf::Vector2f newPosition)
{
	this->sprite.setPosition(newPosition);
	return true; // [HU] ezen meg van amit dolgozni / nem vegleges / lehet folosleges
}

