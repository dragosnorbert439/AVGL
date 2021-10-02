#include "game.h"

// [EN] Private functions
void Game::initializeVariables()
{
	this->window = nullptr;
    this->gameOver = false;
}

void Game::initializeWindow()
{
	this->videoMode.height = 8 * TILE_SIZE;
	this->videoMode.width = 8 * TILE_SIZE;
	// [HU] teljes kepernyonek // this->videoMode.getDesktopMode();
	this->window = new sf::RenderWindow(this->videoMode, "AVGL", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initializePlayer()
{
    this->player = new Player();
}

void Game::initializeMap()
{
    /*
        [HU]    Ez oldja meg a palyat
                Egyelore csak hard kodolt
    */


}

// [EN] Constructor, Destructor
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
    this->initializePlayer();
}

Game::~Game()
{
	delete this->window;
    delete this->player;
}

// [EN] Accessors
const bool Game::isRunning() const
{
	return this->window->isOpen();
}


// [EN] Functions
void Game::update()
{
    this->pollEvents();
    this->player->update(this->window);
}

void Game::render()
{
    this->window->clear(sf::Color(0, 0, 0, 255));

    // [EN] Drawing here
    // [HU] Itt (ujra)rajzolja
    this->player->render(this->window);

    this->window->display();
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape) this->window->close();
            break;
        }
    }
}
