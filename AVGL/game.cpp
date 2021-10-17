#include "game.h"

// [EN] Private functions
void Game::initializeVariables()
{
	this->window = nullptr;
    this->gameOver = false;
}

void Game::initializeWindow()
{
	this->videoMode.height = this->gameRows * TILE_SIZE;
	this->videoMode.width = this->gameCols * TILE_SIZE;
	// [HU] teljes kepernyonek // this->videoMode.getDesktopMode();
	this->window = new sf::RenderWindow(this->videoMode, "AVGL", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initializePlayer()
{
    this->player = new Player(100.f, 100.f);
    this->player->setDT(&this->dt);
    this->player->setGameEvent(&this->event);
    this->player->setGameRenderWindow(&this->window);
}

void Game::initializeTiles()
{
    /*
        [HU]    Ez oldja meg a palyat
                Egyelore csak hard kodolt
    */

    this->tiles.clear();

    std::vector<GameTile*> row;

    std::ifstream fin("testMapFile.txt");
    if (!fin.is_open()) exit(1);
    
    unsigned int v;
    for (int i = 0; i < this->gameRows; ++i)
    {
        row.erase(row.begin(), row.end());

        for (int j = 0; j < this->gameCols; ++j)
        {
            fin >> v;

            if (v == 1)
            {
                row.push_back(new GameTile("C:/Egyetem/Allamvizsga/images/wall.png", j * TILE_SIZE, i * TILE_SIZE, GameTile::UNPASSABLE));
            }
            else
            {
                row.push_back(new GameTile("C:/Egyetem/Allamvizsga/images/ground.png", j * TILE_SIZE, i * TILE_SIZE, GameTile::PASSABLE));
            }
        }

        this->tiles.push_back(row);
    }

    fin.close();

    /*
    for (int i = 0; i < this->gameRows; ++i)
    {
        row.erase(row.begin(), row.end());

        for (int j = 0; j < this->gameCols; ++j)
        {
            if (i == 0 && j == 3)
            {
                row.push_back(new GameTile("C:/Egyetem/Allamvizsga/images/ground.png", j * TILE_SIZE, i * TILE_SIZE, GameTile::PASSABLE));
            }
            else if (i == 1 && j == 4)
            {
                row.push_back(new GameTile("C:/Egyetem/Allamvizsga/images/wall.png", j * TILE_SIZE, i * TILE_SIZE, GameTile::UNPASSABLE));
            }
            else if (i == 4 && j == 4 || i == 5 && j == 4 || i == 6 && j == 4)
            {
                row.push_back(new GameTile("C:/Egyetem/Allamvizsga/images/wall.png", j * TILE_SIZE, i * TILE_SIZE, GameTile::UNPASSABLE));
            }
            else if (!i || !j || i == this->gameRows - 1 || j == this->gameCols - 1)
            {
                row.push_back(new GameTile("C:/Egyetem/Allamvizsga/images/wall.png", j * TILE_SIZE, i * TILE_SIZE, GameTile::UNPASSABLE));
            }
            else
            {
                row.push_back(new GameTile("C:/Egyetem/Allamvizsga/images/ground.png", j * TILE_SIZE, i * TILE_SIZE, GameTile::PASSABLE));
            }
        }

        tiles.push_back(row);
    }
    */
}

// [EN] Constructor, Destructor
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
    this->initializeTiles();
    this->initializePlayer();
}

Game::~Game()
{
    for (int i = 0; i < gameRows; ++i) for (int j = 0; j < gameCols; ++j) delete tiles.at(i).at(j);
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
    // [EN] Event polling
    // [HU] Esemeny kezelo
    this->pollEvents();

    // [EN] Update here
    // [HU] Itt frissit
    for (int i = 0; i < this->gameRows; ++i)
    {
        for (int j = 0; j < this->gameCols; ++j)
        {
            this->tiles[i][j]->update(this->window);
        }
    }

    this->player->update(this->window, this->tiles);
}

void Game::render()
{
    this->window->clear(sf::Color(0, 0, 0, 255));

    // [EN] Drawing here
    // [HU] Itt (ujra)rajzoljas

    for (int i = 0; i < this->gameRows; ++i)
    {
        for (int j = 0; j < this->gameCols; ++j)
        {
            this->tiles[i][j]->render(this->window);
        }
    }

    this->player->render(this->window);

    // [HU] Itt hajtja vegre
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

void Game::setDeltaTime(const float value)
{
    this->dt = value;
}

float Game::getDeltaTime() const
{
    return this->dt;
}
