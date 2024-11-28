#include "Request.h"

Engine::Request::Request(Sprite* foodSprite, Sprite* checklistSprite, Text* amountText)
{
	this->sprite = foodSprite;
	this->checklistSprite = checklistSprite;
	this->amountText = amountText;
	state = Engine::RequestState::DIE;
	this->fixFoodY = sprite->GetPosition().y;
	this->fixChecklistY = checklistSprite->GetPosition().y;
	this->fixAmountTextY = amountText->GetPosition().y;
}

Engine::Request::~Request()
{

}

void Engine::Request::Update(float deltaTime, bool moveUp)
{
	float foodY = sprite->GetPosition().y;
	float checklistY = checklistSprite->GetPosition().y;
	float amountTextY = amountText->GetPosition().y;
	float yVelocity = 0.2f;
	if (moveUp) {
		foodY += yVelocity * deltaTime;
		checklistY += yVelocity * deltaTime;
		amountTextY += yVelocity * deltaTime;
	}
	else {
		foodY -= yVelocity * deltaTime;
		checklistY -= yVelocity * deltaTime;
		amountTextY -= yVelocity * deltaTime;
		if (foodY < fixFoodY) foodY = fixFoodY;
		if (checklistY < fixChecklistY) checklistY = fixChecklistY;
		if (amountTextY < fixAmountTextY) amountTextY = fixAmountTextY;
	}
	sprite->SetYPosition(foodY);
	checklistSprite->SetYPosition(checklistY);
	amountText->SetYPosition(amountTextY);
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
	amountText->SetText(amountStr);
	state = Engine::RequestState::UNFULLFILLED;
	return this;
}

Engine::Request* Engine::Request::SetFullfilled()
{
	this->state = Engine::RequestState::FULLFILLED;
	return this;
}

Engine::Request* Engine::Request::SetDie()
{
	this->state = Engine::RequestState::DIE;
	return this;
}

Engine::Request* Engine::Request::SetFoodFrame(int frameIndex) {
	sprite->SetFrame(frameIndex);
	return this;
}
