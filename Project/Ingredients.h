#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include "Sprite.h"

namespace Engine {
	enum class IngredientsState {
		SPAWN,
		GROUND,
		DIE
	};
	class Ingredients
	{
	public:
		Ingredients(Sprite* sprite);
		~Ingredients();
		void Update(float deltaTime);
		void Draw();
		Ingredients* SetPosition(float x, float y);
		Ingredients* SetSpawn();
		float GetWidth();
		float GetHeight();
		bool IsDie();
		float GetX();
		float GetY();
		Ingredients* SetFrame(int frameIndex);
	protected:
		Sprite* sprite = NULL;
		IngredientsState state;
		float groundDur = 0, groundTime = 0, x = 0, y = 0;
	};

}

#endif#pragma once
