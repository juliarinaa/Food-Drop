#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H

#include "Screen.h"
#include "ScreenManager.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Food.h"
#include "Heart.h"
#include "Text.h"
#include "Sound.h"
#include "Music.h"
#include "Request.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include "RestartMenuScreen.h"

namespace Engine {
	class GamePlayScreen :
		public Engine::Screen
	{
	public:
		GamePlayScreen();
		~GamePlayScreen();
		void Init();
		void Update();
		void Draw();
		void ResetGameState();
		void SaveHighestScore(int score);
		GamePlayScreen* PlayMusic();
		GamePlayScreen* SetHighestScore(int score);
	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* CreateSprite();
		Engine::Sprite* backgroundSprite = NULL;
		Engine::Sprite* scoreBoardSprite = NULL;
		Engine::Texture* overlayBlackTexture = NULL;
		Engine::Sprite* overlayBlackSprite = NULL;
		Engine::Texture* overlayWhiteTexture = NULL;
		Engine::Sprite* overlayWhiteSprite = NULL;
		Engine::Texture* notesTexture = NULL;
		Engine::Sprite* notesSprite = NULL;

		// Request
		map<int, int> request;
		vector<Request*> requestAssets;
		int foodTypeAmount = 0;
		vector<int> unfulfilledRequest;

		// Basket
		Engine::Texture* basketTexture = NULL;
		Engine::Sprite* basketSprite = NULL;

		Food* SpawnObjects();

		vector<Engine::Food*> objects;
		vector<Engine::Heart*> hearts;

		float spawnDuration = 0,
			maxSpawnTime = 0,
			numObjectsInPool = 0,
			numObjectPerSpawn = 0,
			minXBasket = 0,
			maxXBasket = 0,
			marginX = 0,
			basketVelocity = 0.4f;

		Text* scoreTitle = NULL;
		Text* scoreText = NULL;
		Text* orderTitle = NULL;
		float fixOrderTitleY = 0;

		string FormatScore(int score);
		Text* bonusScoreText = NULL;
		int score = 0, bonusScore = 0;
		float bonusScoreDuration = 1000;
		bool showBonusScore = false;
		
		bool gameOver = false;
		bool moveUp = true;
		bool allRequestFullfilled = false;

		Sound* correctSound = NULL;
		Sound* wrongSound = NULL;
		Sound* completeSound = NULL;
		Sound* gameOverSound = NULL;
		Music* music = NULL;

		Food* currFood = NULL;

		float foodVelocity = 0.2f;
		int highestScore = 0;
	};
}
#endif
#pragma once