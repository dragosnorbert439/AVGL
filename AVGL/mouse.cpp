#include "mouse.h"

Mouse::Mouse(float x, float y)
{
	movementSpeed = 10.f;
	shape.setPosition(x, y);
	setUpVariables();
	setUpShape();
}

void Mouse::setUpVariables()
{

}

void Mouse::setUpShape()
{
	shape.setFillColor(sf::Color::Green);
	shape.setSize(sf::Vector2f(50.f, 50.f));
}

Mouse::~Mouse()
{
}

void Mouse::updateMouse()
{
	// Window bounds collision

	updateInputMouse();
}

void Mouse::updateInputMouse()
{
	// Keyboard input

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		shape.move(-movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		shape.move(movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		shape.move(0.f, -movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		shape.move(0.f, movementSpeed);
	}

}