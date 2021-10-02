#include <SFML/Graphics.hpp>

class Mouse
{
	sf::RectangleShape shape;
	void setUpVariables();
	void setUpShape();
	float movementSpeed;

public:
	Mouse(float x = 0.f, float y = 0.f);
	~Mouse();
	void updateMouse();
	void updateInputMouse();
	void renderMouse(sf::RenderTarget* target);
};