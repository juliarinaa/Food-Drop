#include "Food.h"

Engine::Food::Food(Sprite* sprite)
{
	this->sprite = sprite;
	state = Engine::FoodState::DIE;
	groundDur = 0;
	groundTime = 0;
}

Engine::Food::~Food()
{

}

void Engine::Food::Update(float deltaTime, float velocity)
{
	if (state == Engine::FoodState::DIE) {
		return;
	}

	float x = GetX();
	float y = GetY();

	if ((Engine::FoodState::SPAWN == state && y + GetHeight() <= 0) ||
		(Engine::FoodState::CATCHED == state && y <= 0))
	{
		velocity = 0;
		state = Engine::FoodState::DIE;
	}

	y -= velocity * deltaTime;
	sprite->SetPosition(x, y);
}

void Engine::Food::Draw()
{
	if (state == Engine::FoodState::DIE) {
		return;
	}

	sprite->Draw();
}

Engine::Food* Engine::Food::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
	return this;
}

Engine::Food* Engine::Food::SetSpawn()
{
	this->state = Engine::FoodState::SPAWN;
	return this;
}

Engine::Food* Engine::Food::SetCatched()
{
	this->state = Engine::FoodState::CATCHED;
	return this;
}

Engine::Food* Engine::Food::SetDie()
{
	this->state = Engine::FoodState::DIE;
	return this;
}

float Engine::Food::GetWidth()
{
	return sprite->GetScaleWidth();
}

float Engine::Food::GetHeight()
{
	return sprite->GetScaleHeight();
}

int Engine::Food::GetFrameIndex()
{
	return sprite->GetFrameIndex();
}

bool Engine::Food::IsDie()
{
	return Engine::FoodState::DIE == state;
}

bool Engine::Food::IsSpawn()
{
	return Engine::FoodState::SPAWN == state;
}

bool Engine::Food::IsCatched()
{
	return Engine::FoodState::CATCHED == state;
}

float Engine::Food::GetX()
{
	return sprite->GetPosition().x;
}

float Engine::Food::GetY()
{
	return sprite->GetPosition().y;
}

Engine::Food* Engine::Food::SetFrame(int frameIndex) {
	sprite->SetFrame(frameIndex);
	return this;
}

Engine::BoundingBox* Engine::Food::GetBoundingBox() 
{
	return sprite->GetBoundingBox();
}





