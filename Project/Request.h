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
		void Update(float deltaTime, bool noteGone);
		void Draw();
		int GetFoodFrameIndex();
		Request* SetAmount(int amount);
		Request* SetFoodFrame(int frameIndex);
		Request* SetFullfilled();
		Request* SetDie();
	protected:
		Sprite* sprite = NULL;
		Sprite* checklistSprite = NULL;
		Text* amountText = NULL;
		RequestState state;
	private:
		float fixFoodY = 0;
		float fixAmountTextY = 0;
		float fixChecklistY = 0;
	};

}

#endif#pragma once
