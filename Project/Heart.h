#ifndef HEART_H
#define HEART_H

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
		Heart* PlayAnim(string name);
		Heart* SetDie();
		Heart* SetExist();
		float GetWidth();
		float GetHeight();
		bool IsDie();
		float GetX();
		float GetY();
	protected:
		Sprite* sprite = NULL;
		HeartState state;
		float x = 0, y = 0;
	};

}

#endif