#ifndef FOODDROPGAME_H
#define FOODDROPGAME_H

#include "Game.h"
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

namespace Engine {
	class FoodDropGame :public Engine::Game
	{
	public:
		FoodDropGame(Setting* setting);
		~FoodDropGame();
		virtual void Init();
		virtual void Update();
		virtual void Render();
		void ResetGameState();
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

		/*void SpawnObjects();*/
		Food* SpawnObjects();

		vector<Engine::Food*> objects;
		vector<Engine::Heart*> hearts;

		float spawnDuration = 0,
			maxSpawnTime = 0,
			numObjectsInPool = 0,
			numObjectPerSpawn = 0,
			minXBasket = 0,
			maxXBasket = 0,
			marginX = 0;

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
		Sound* changeNoteSound = NULL;
		Music* music = NULL;

		//debugging dot
		Engine::Texture* dotTexture = NULL;

		Engine::Sprite* dot = NULL;

		//Sprite* dotSprite1 = NULL;
		//Sprite* dotSprite2 = NULL;
		//Sprite* dotSprite3 = NULL;
		//Sprite* dotSprite4 = NULL;
		Food* currFood = NULL;

		float foodVelocity = 0.2f;
	};
}
#endif
#pragma once