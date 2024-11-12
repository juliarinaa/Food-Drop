#include "Ingredients.h"

Engine::Ingredients::Ingredients(Sprite* sprite)
{
	this->sprite = sprite;
	state = Engine::IngredientsState::DIE;
	groundDur = 0;
	groundTime = 0;
}

Engine::Ingredients::~Ingredients()
{

}

void Engine::Ingredients::Update(float deltaTime)
{
	if (state == Engine::IngredientsState::DIE) {
		return;
	}

	float x = GetX();
	float y = GetY();
	float yVelocity = 0.2f;

	if (Engine::IngredientsState::SPAWN == state && y <= 0) {
		state = Engine::IngredientsState::GROUND;
	}

	if (state == Engine::IngredientsState::GROUND) {
		yVelocity = 0;
		if (groundDur >= groundTime) {
			state = Engine::IngredientsState::DIE;
			groundDur = 0;
		}
		groundDur += deltaTime;
	}

	y -= yVelocity * deltaTime;
	sprite->SetPosition(x, y);
	sprite->Update(deltaTime);
}

void Engine::Ingredients::Draw()
{
	if (state == Engine::IngredientsState::DIE) {
		return;
	}

	sprite->Draw();
}



Engine::Ingredients* Engine::Ingredients::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
	return this;
}

Engine::Ingredients* Engine::Ingredients::SetSpawn()
{
	this->state = Engine::IngredientsState::SPAWN;
	return this;
}

float Engine::Ingredients::GetWidth()
{
	return sprite->GetScaleWidth();
}

float Engine::Ingredients::GetHeight()
{
	return sprite->GetScaleHeight();
}

bool Engine::Ingredients::IsDie()
{
	return Engine::IngredientsState::DIE == state;
}

float Engine::Ingredients::GetX()
{
	return sprite->GetPosition().x;
}

float Engine::Ingredients::GetY()
{
	return sprite->GetPosition().y;
}

Engine::Ingredients* Engine::Ingredients::SetFrame(int frameIndex) {
	sprite->SetFrame(frameIndex);
	return this;
}

Engine::BoundingBox* Engine::Ingredients::GetBoundingBox() 
{
	return sprite->GetBoundingBox();
}





