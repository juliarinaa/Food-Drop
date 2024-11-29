#include "Heart.h"

Engine::Heart::Heart(Sprite* sprite)
{
	this->sprite = sprite;
	state = Engine::HeartState::EXIST;
}

Engine::Heart::~Heart()
{

}

void Engine::Heart::Update(float deltaTime)
{
	if(Engine::HeartState::DIE == state) sprite->PlayAnimOnce(deltaTime);
}

void Engine::Heart::Draw()
{
	sprite->Draw();
}

Engine::Heart* Engine::Heart::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
	return this;
}

float Engine::Heart::GetWidth()
{
	return sprite->GetScaleWidth();
}

float Engine::Heart::GetHeight()
{
	return sprite->GetScaleHeight();
}

bool Engine::Heart::IsDie()
{
	return Engine::HeartState::DIE == state;
}

Engine::Heart* Engine::Heart::SetDie()
{
	this->state = Engine::HeartState::DIE;
	return this;
}

Engine::Heart* Engine::Heart::SetExist()
{
	this->state = Engine::HeartState::EXIST;
	sprite->SetFrame(0);
	return this;
}

float Engine::Heart::GetX()
{
	return sprite->GetPosition().x;
}

float Engine::Heart::GetY()
{
	return sprite->GetPosition().y;
}

Engine::Heart* Engine::Heart::PlayAnim(string name)
{
	sprite->PlayAnim(name);
	return this;
}