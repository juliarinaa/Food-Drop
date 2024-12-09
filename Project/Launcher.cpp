#include "Setting.h"
#include "Game.h"

#include "GamePlayScreen.h"
#include "FoodDropGame.h"

int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->screenWidth = 640;
	setting->screenHeight = 360;
	setting->windowFlag = Engine::WindowFlag::FULLSCREEN;
	setting->vsync = false;
	setting->targetFrameRate = 75;
	Engine::Game* game = new Engine::FoodDropGame(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}
