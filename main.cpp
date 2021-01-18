

#include <string>
#include "game/Game.h"
#include "support/Logger.h"

int main(int argc ,char ** argv) {
    {
        Logger::Init(LOGGER_FULL , "|TEST|");
        const string a(argv[0]);
        ResourcesManager::setDefaultPath(a);
        Game* game = new Game();
        game->setFPS(59);

        Logger::LogData("---||EngineStart||---");
        game->start();
        delete game;
        Logger::LogData("---||EngineEnd||---");
    }


    exit(0);
}
//status 0 - Normal Exit
//status 3 - Shader Error Compile
