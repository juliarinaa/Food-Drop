#ifndef RESTARTMENUSCREEN_H
#define RESTARTMENUSCREEN_H

#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include <vector>
#include "ScreenManager.h"
#include "MainMenuScreen.h"
#include "GamePlayScreen.h"

namespace Engine {
	class RestartMenuScreen :
		public Engine::Screen
	{
	public:
		RestartMenuScreen();
		void Init();
		void Update();
		void Draw();
		void SetFinalScore(int finalScore);
		void SetHighestScore(int highestScore);
	private:
		vector<Button*> buttons;
		Text* text;
		Text* textGameOver;
		int currentButtonIndex = 0;
		Sprite* bgSprite;
		Sprite* restartSprite;
		Sprite* titleGameOver;
		int finalScore = 0;
		int highestScore = 0;

	};
}

#endif