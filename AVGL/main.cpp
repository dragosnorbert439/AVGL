#include "game.h"
#include "configSrc.cpp"
#include "gameWorld.h"
#include "gameTile.h"

int main()
{
    // [EN] Game init
    // [HU] Jatek inicializalasa
    Game game;

    // [EN] Game loop
    // [HU] Jatek folyamat - ciklus
    while (game.isRunning())
    {
        // [EN] Event polling
        // [HU] Esemeny erzekelo
        /*
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            else gameWorld.update();

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) window.close();
                break;

            }
        }*/


        // [EN] Update
        // [HU] Frissit
        game.update();

        // [EN] Render
        // [HU] Ujrarajzol
        game.render();

        /*
        window.clear();

        for (int i = 0; i < gameWorld.gridLength; ++i)
        {
            for (int j = 0; j < gameWorld.gridLength; ++j)
            {
                window.draw(gameWorld.tiles[i][j]->sprite);
            }
        }

        window.display();*/
    }

    // [EN] End of application
    // [HU] Alkalmazas vege
    return 0;
}