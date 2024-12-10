#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Music.h"
#include "Text.h"
#include "GamePlayScreen.h"
#include <vector>
#include "ScreenManager.h"

namespace Engine {
	class MainMenuScreen :
		public Engine::Screen
	{
	public:
		MainMenuScreen();
		void Init();
		void Update();
		void Draw();
		int LoadHighestScore();
		MainMenuScreen* PlayMusic();
		MainMenuScreen* SetHighestScore(int highestScore);
	private:
		Sprite* background = NULL;
		Sprite* title = NULL;
		Sprite* playSprite = NULL;
		Music* music = NULL;
		vector<Button*> buttons;
		Text* textHighestScore;
		int currentButtonIndex = 0;
		int highestScore = 0;
		bool firstTime = true;
	};
}

#endif