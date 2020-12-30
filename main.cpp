
#include "game/Game.h"

int main() {
    {
        Game* game = new Game();
        game->setFPS(15);
        game->start();
        delete game;
    }
    exit(0);
}
//status 0 - Normal Exit