#ifndef REQUEST_H
#define REQUEST_H

#include "Sprite.h"
#include "Text.h"

namespace Engine {
	enum class RequestState {
		UNCOMPLETE,
		COMPLETE,
		DIE
	};
	class Request
	{
	public:
		Request(Sprite* sprite, Text* amountText);
		~Request();
		void Update(float deltaTime);
		void Draw();
		float GetFoodWidth();
		float GetFoodHeight();
		float GetX();
		float GetY();
		int GetFoodFrameIndex();
		Request* SetAmount(int amount);
		Request* SetFoodPosition(float x, float y);
		Request* SetTextPosition(float x, float y);
		Request* SetFoodFrame(int frameIndex);
	protected:
		Sprite* sprite = NULL;
		Text* amountText = NULL;
		RequestState state;
		float x = 0, y = 0;
	};

}

#endif#pragma once
