#include "GameManager.h"

using SDLFramework::GameManager;

int main(int argc, char * args[])
{
	srand(static_cast<unsigned int>(time(0)));
	GameManager * game = GameManager::Instance();

	game->Run();

	GameManager::Release();
	game = nullptr;

	return 0;
}