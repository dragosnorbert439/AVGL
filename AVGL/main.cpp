#include "game.h"
#include "configSrc.cpp"
#include "gameWorld.h"
#include "gameTile.h"

int main()
{
    // [EN] Game init
    // [HU] Jatek inicializalasa
    Game game;
    sf::Clock dt_clock;

    // [EN] Game loop
    // [HU] Jatek folyamat - ciklus
    while (game.isRunning())
    {
        game.setDeltaTime(dt_clock.restart().asSeconds());

        // [EN] Update
        // [HU] Frissit
        game.update();

        // [EN] Render
        // [HU] Ujrarajzol
        game.render();
    }

    // [EN] End of application
    // [HU] Alkalmazas vege
    return 0;
}