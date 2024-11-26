#ifndef REQUEST_H
#define REQUEST_H

#include "Sprite.h"
#include "Text.h"

namespace Engine {
	enum class RequestState {
		UNFULLFILLED,
		FULLFILLED,
		DIE
	};
	class Request
	{
	public:
		Request(Sprite* foodSprite, Sprite* checklistSprite,Text* amountText);
		~Request();
		void Update(float deltaTime);
		void Draw();
		int GetFoodFrameIndex();
		Request* SetAmount(int amount);
		Request* SetFoodFrame(int frameIndex);
		Request* SetFullfilled();
	protected:
		Sprite* sprite = NULL;
		Sprite* checklistSprite = NULL;
		Text* amountText = NULL;
		RequestState state;
		float x = 0, y = 0;
	};

}

#endif#pragma once
