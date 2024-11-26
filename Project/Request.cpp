#include "Request.h"

Engine::Request::Request(Sprite* foodSprite, Sprite* checklistSprite, Text* amountText)
{
	this->sprite = foodSprite;
	this->checklistSprite = checklistSprite;
	this->amountText = amountText;
	state = Engine::RequestState::UNFULLFILLED;
}

Engine::Request::~Request()
{

}

void Engine::Request::Update(float deltaTime)
{
	/*if (state == Engine::RequestState::DIE) {
		return;
	}

	float x = GetX();
	float y = GetY();
	float yVelocity = 0.2f;

	y -= yVelocity * deltaTime;
	sprite->SetPosition(x, y);
	sprite->Update(deltaTime);*/
}

void Engine::Request::Draw()
{
	if (state == Engine::RequestState::DIE) {
		return;
	}
	sprite->Draw();
	if (state == Engine::RequestState::UNFULLFILLED) amountText->Draw();
	else checklistSprite->Draw();
}

int Engine::Request::GetFoodFrameIndex()
{
	return sprite->GetFrameIndex();
}

Engine::Request* Engine::Request::SetAmount(int amount) 
{
	std::string amountStr = "x " + std::to_string(amount);
	std::cout << "Updating amount: " << amountStr << std::endl;  // Debugging line
	this->amountText->SetText(amountStr);
	return this;
}

Engine::Request* Engine::Request::SetFullfilled()
{
	this->state = Engine::RequestState::FULLFILLED;
	return this;
}

Engine::Request* Engine::Request::SetFoodFrame(int frameIndex) {
	sprite->SetFrame(frameIndex);
	return this;
}
