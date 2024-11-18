#ifndef COOKNCOLLECT_H
#define COOKNCOLLECT_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Ingredients.h"
#include "Heart.h"
#include "Text.h"
#include "Sound.h"
#include <vector>
#include <sstream>
#include <iomanip>

namespace Engine {
	class CookNCollect :public Engine::Game
	{
	public:
		CookNCollect(Setting* setting);
		~CookNCollect();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* CreateSprite();
		Engine::Sprite* backgroundSprite = NULL;
		Engine::Texture* overlayBlackTexture = NULL;
		Engine::Sprite* overlayBlackSprite = NULL;
		Engine::Texture* overlayWhiteTexture = NULL;
		Engine::Sprite* overlayWhiteSprite = NULL;

		Engine::Texture* basketTexture = NULL;
		Engine::Sprite* basketSprite = NULL;

		void SpawnObjects();

		vector<Engine::Ingredients*> objects;
		vector<Engine::Heart*> hearts;

		float spawnDuration = 0,
			maxSpawnTime = 0,
			numObjectsInPool = 0,
			numObjectPerSpawn = 0,
			minXBasket = 0,
			maxXBasket = 0,
			marginX = 0;

		Text* scoreText = NULL;
		string FormatScore(int score);
		int score = 0;
		
		bool gameOver = false;

		Sound* correctSound = NULL;

		//debugging dot
		Engine::Texture* dotTexture = NULL;
		Engine::Sprite* dot = NULL;

		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;
	};
}
#endif
#pragma once