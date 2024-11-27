#ifndef FOOD_H
#define FOOD_H

#include "Sprite.h"

namespace Engine {
	enum class FoodState {
		SPAWN,
		GROUND,
		CATCHED,
		DIE
	};
	class Food
	{
	public:
		Food(Sprite* sprite);
		~Food();
		void Update(float deltaTime, float velocity);
		void Draw();
		Food* SetPosition(float x, float y);
		Food* SetSpawn();
		Food* SetDie();
		Food* SetCatched();
		float GetWidth();
		float GetHeight();
		bool IsDie();
		bool IsCatched();
		bool IsSpawn();
		float GetX();
		float GetY();
		int GetFrameIndex();
		Food* SetFrame(int frameIndex);
		BoundingBox* GetBoundingBox();
	protected:
		Sprite* sprite = NULL;
		FoodState state;
		float groundDur = 0, groundTime = 0, x = 0, y = 0;
	private:
	};

}

#endif#pragma once
