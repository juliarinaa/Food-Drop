#include "CookNCollect.h"

Engine::CookNCollect::CookNCollect(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Object Pool";
}

Engine::CookNCollect::~CookNCollect()
{
	delete texture;
	delete basketTexture;
	delete basketSprite;
}

void Engine::CookNCollect::Init()
{
	// Basket
	texture = new Texture("basket.png");
	basketSprite = (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetScale(0.3);
	basketSprite->SetPosition(setting->screenWidth / 2 - basketSprite->GetScaleWidth() / 2, 0);

	inputManager->AddInputMapping("slide-left", SDLK_LEFT)->AddInputMapping("slide-right", SDLK_RIGHT);

	minXBasket = (int)(setting->screenWidth / 3);
	maxXBasket = (int)(setting->screenWidth * 2 / 3 - basketSprite->GetScaleWidth());

	// Spawn setting
	maxSpawnTime = 1000;
	numObjectPerSpawn = 1;
	numObjectsInPool = 100;

	// Load a texture
	texture = new Texture("foods.png");
	for (int i = 0; i < numObjectsInPool; i++) {
		Ingredients* o = new Ingredients(CreateSprite());
		objects.push_back(o);
	}
	// Set background
	SetBackgroundColor(201, 130, 130);

	// Add input
	inputManager->AddInputMapping("quit", SDLK_ESCAPE);
}

void Engine::CookNCollect::Update()
{
	if (inputManager->IsKeyReleased("quit")) {
		state = Engine::State::EXIT;
	}

	// basket movement -> berdasarkan lesson 05
	float x = basketSprite->GetPosition().x;
	float y = basketSprite->GetPosition().y;
	float velocity = 0.4f;
	// s = v * t;
	if (inputManager->IsKeyPressed("slide-right")) {
		if (x <= maxXBasket) {
			x += velocity * GetGameTime();
			basketSprite->SetPosition(x, y)->Update(GetGameTime());
		}
	}

	if (inputManager->IsKeyPressed("slide-left")) {
		if (x >= minXBasket) {
			x -= velocity * GetGameTime();
			basketSprite->SetPosition(x, y)->Update(GetGameTime());
		}
	}

	// Time to spawn objects
	if (spawnDuration >= maxSpawnTime) {
		SpawnObjects();
		spawnDuration = 0;
	}
	// Update all objects
	for (Ingredients* o : objects) {
		o->Update(GetGameTime());
	}
	// Count spawn duration
	spawnDuration += GetGameTime();
}

void Engine::CookNCollect::Render()
{
	// Render all objects
	for (Ingredients* o : objects) {
		o->Draw();
	}
	basketSprite->Draw();
}

/*
* Helper method to create a custom sprite
*/
Engine::Sprite* Engine::CookNCollect::CreateSprite()
{
	return (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetNumXFrames(3)->SetNumYFrames(3)->AddAnimation("hit", 2, 4)->AddAnimation("spikes", 5, 12)->AddAnimation("idle-1", 14, 27)->AddAnimation("idle-2", 28, 41)->AddAnimation("spikes-out", 42, 49)->PlayAnim("idle-1")->SetScale(4)->SetAnimationDuration(100);

}

void Engine::CookNCollect::SpawnObjects()
{
	//Find Die object to reuse for spawning
	int spawnCount = 0;
	for (Ingredients* o : objects) {
		if (spawnCount == numObjectPerSpawn) {
			break;
		}
		if (o->IsDie()) {
			// Set state to spawn
			o->SetSpawn();

			o->SetFrame(rand() % 9);

			// Random spawn position
			int min = (int)(setting->screenWidth/3);
			int max = (int)(setting->screenWidth*2/3 - o->GetWidth());
			float x = (float)(rand() % (max - min + 1) + min);
			float y = setting->screenHeight + o->GetHeight();
			o->SetPosition(x, y);
			spawnCount++;
		}
	}
}



