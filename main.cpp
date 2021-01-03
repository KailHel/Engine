#include <string>
#include "game/Game.h"

int main(int argc, char** argv) {
	{
		const string a(argv[0]);
		ResourcesManager::setDefaultPath(a);
		Game* game = new Game();
		game->setFPS(59);
		game->start();
		delete game;
	}

	exit(0);
}
//status 0 - Normal Exit
//status 3 - Shader Error Compile