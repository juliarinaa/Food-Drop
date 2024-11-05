#ifndef COOKNCOLLECT_H
#define COOKNCOLLECT_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Ingredients.h"
#include <vector>

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
		void SpawnObjects();
		vector<Engine::Ingredients*> objects;
		float spawnDuration = 0, maxSpawnTime = 0, numObjectsInPool = 0, numObjectPerSpawn = 0;
	};
}
#endif
#pragma once