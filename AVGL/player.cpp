#include "player.h"

// [EN] Private functions
void Player::initializeVariables()
{
	this->movementSpeed = 10.f;
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
	this->setPosition(sf::Vector2f(x, y));
}

Player::~Player()
{
}


// [EN] Functions
void Player::update(const sf::RenderTarget* target)
{
	// [EN] Keyboard input (funciton call)
	this->updateInput();
	
	// [EN] Window bound collision
	this->updateWindowBoundsCollision(target);
}

void Player::updateInput()
{
	// [EN] Keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sprite.move(-movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sprite.move(movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		sprite.move(0.f, -movementSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		sprite.move(0.f, movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
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

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}


// [EN] Getter, Setter
sf::Vector2f Player::getPosition() const
{
	return this->position;
}

bool Player::setPosition(const sf::Vector2f newPosition)
{

	return true; // [HU] ezen meg van amit dolgozni / nem vegleges
}

