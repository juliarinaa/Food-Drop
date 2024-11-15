#ifndef TURTLE_H
#define TURTLE_H

#include "Sprite.h"

namespace Engine {
	enum class HeartState {
		EXIST,
		DIE
	};
	class Heart
	{
	public:
		Heart(Sprite* sprite);
		~Heart();
		void Update(float deltaTime);
		void Draw();
		Heart* SetPosition(float x, float y);
		Heart* SetSpawn();
		float GetWidth();
		float GetHeight();
		bool IsDie();
		float GetX();
		float GetY();
	protected:
		Sprite* sprite = NULL;
		HeartState state;
		float groundDur = 0, groundTime = 0, x = 0, y = 0;
	};

}

#endif