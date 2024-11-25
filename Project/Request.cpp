#include "Request.h"

Engine::Request::Request(Sprite* sprite, Text* amountText)
{
	this->sprite = sprite;
	this->amountText = amountText;
	state = Engine::RequestState::UNCOMPLETE;
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
	amountText->Draw();
}

Engine::Request* Engine::Request::SetFoodPosition(float x, float y)
{
	sprite->SetPosition(x, y);
	return this;
}

Engine::Request* Engine::Request::SetTextPosition(float x, float y)
{
	amountText->SetPosition(x, y);
	return this;
}

float Engine::Request::GetFoodWidth()
{
	return sprite->GetScaleWidth();
}

float Engine::Request::GetFoodHeight()
{
	return sprite->GetScaleHeight();
}

int Engine::Request::GetFoodFrameIndex()
{
	return sprite->GetFrameIndex();
}

float Engine::Request::GetX()
{
	return sprite->GetPosition().x;
}

Engine::Request* Engine::Request::SetAmount(int amount) 
{
	std::string amountStr = "x " + std::to_string(amount);
	std::cout << "Updating amount: " << amountStr << std::endl;  // Debugging line
	this->amountText->SetText(amountStr);
	return this;
}

float Engine::Request::GetY()
{
	return sprite->GetPosition().y;
}

Engine::Request* Engine::Request::SetFoodFrame(int frameIndex) {
	sprite->SetFrame(frameIndex);
	return this;
}
