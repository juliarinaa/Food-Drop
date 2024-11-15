#include "Heart.h"

Engine::Heart::Heart(Sprite* sprite)
{
	this->sprite = sprite;
	state = Engine::HeartState::DIE;
	groundDur = 0;
	groundTime = 3000;
}

Engine::Heart::~Heart()
{

}

//void Engine::Heart::Update(float deltaTime)
//{
//	if (sprite->frameIndex == endFrameIndex)
//		return;
//
//	frameDuration += deltaTime;
//
//	if (frameDuration >= maxFrameDuratin) {
//		frameDuration = 0;
//		if(frameIndex < 4) frameIndex
//		frameIndex = (frameIndex < currentAnim->startFrameIndex || frameIndex == currentAnim->endFrameIndex) ? currentAnim->startFrameIndex : frameIndex;
//	}
//}

void Engine::Heart::Draw()
{
	if (state == Engine::HeartState::DIE) {
		return;
	}

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

float Engine::Heart::GetX()
{
	return sprite->GetPosition().x;
}

float Engine::Heart::GetY()
{
	return sprite->GetPosition().y;
}