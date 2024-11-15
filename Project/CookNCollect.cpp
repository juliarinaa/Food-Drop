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
	delete scoreText;
}

void Engine::CookNCollect::Init()
{
	// Sound Effect
	correctSound = (new Sound("catch.wav"))->SetVolume(100);

	// Basket
	texture = new Texture("basket.png");
	basketSprite = (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetScale(0.3);
	basketSprite->SetPosition(setting->screenWidth / 2 - basketSprite->GetScaleWidth() / 2, 0);

	inputManager->AddInputMapping("slide-left", SDLK_LEFT)->AddInputMapping("slide-right", SDLK_RIGHT);

	minXBasket = (int)(setting->screenWidth / 3);
	maxXBasket = (int)(setting->screenWidth * 2 / 3 - basketSprite->GetScaleWidth());

	// dot buat debugging aj
	dotTexture = new Texture("dot.png");
	dot = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dot->SetPosition((int)setting->screenWidth / 2, basketSprite->GetScaleHeight() - 5);

	dotSprite1 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite2 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite3 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite4 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	
	// Spawn setting
	maxSpawnTime = 1000;
	numObjectPerSpawn = 1;
	numObjectsInPool = 100;

	// Load ingredient texture
	texture = new Texture("foods.png");
	for (int i = 0; i < numObjectsInPool; i++) {
		Ingredients* o = new Ingredients(CreateSprite());
		objects.push_back(o);
	}

	// Set background
	SetBackgroundColor(201, 130, 130);

	// Add input
	inputManager->AddInputMapping("quit", SDLK_ESCAPE);
	
	// Score text setting
	scoreText = new Text("ARCADECLASSIC.ttf", 40, defaultTextShader);
	scoreText->SetColor(255, 255, 255)->SetPosition(25, setting->screenHeight - scoreText->GetFontSize() - 5);
	scoreText->SetText("0000000");

	//load heart texture
	texture = new Texture("heart.png");
	for (int i = 0; i < 3; i++) {
		Heart* o = new Heart((new Sprite(texture, defaultSpriteShader, defaultQuad))->SetNumXFrames(5)->SetNumYFrames(1)->AddAnimation("gone", 0, 4)->SetScale(2.5)->SetAnimationDuration(150));
		hearts.push_back(o);
	}

	// set heart position
	for (size_t i = 0; i < 3; i++)
	{
		hearts[i]->SetPosition(setting->screenWidth - (i + 1) * hearts[i]->GetWidth() - (25 + i*10), setting->screenHeight - hearts[i]->GetHeight()-25);
	}

	// nyoba animasi
	hearts[0]->PlayAnim("gone");
}

void Engine::CookNCollect::Update()
{
	// quit button
	if (inputManager->IsKeyReleased("quit")) {
		state = Engine::State::EXIT;
	}

	if (!gameOver) {
		// Update all objects
		for (Ingredients* o : objects) {
			o->Update(GetGameTime());
			// detect coallision and update score
			// kalo misal si makanan itu berada di deket keranjang dan dia blm menghilang dari 
			// layar ataupun pernah ketangkap sebelumnya dan ada tabrakan dengan keranjang maka...
			if (o->GetY() <= basketSprite->GetScaleHeight()
				&& o->GetY() >= (basketSprite->GetScaleHeight() - 5) 
				&& o->IsSpawn() 
				&& o->GetBoundingBox()->CollideWith(basketSprite->GetBoundingBox())) {
				// misalkan makanan no.8 (telur) itu yg gak bleh ditangkap (buat ngetes pengurangan nyawa)
				if (o->GetFrameIndex() == 8) {
					for (int i = 2; i >= 0; i--)
					{
						if (hearts[i]->IsDie()) continue;
						hearts[i]->PlayAnim("gone")->SetDie();
						break;
					}
				}
				else {
					correctSound->Play(false);
					score += 100;
					scoreText->SetText(FormatScore(score));
				}
				o->SetCatched();
			}
		}

		for (Heart* o : hearts) {
			o->Update(GetGameTime());
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

		// Count spawn duration
		spawnDuration += GetGameTime();
	}

	//Shape for debug
	BoundingBox* bb = objects[1]->GetBoundingBox();
	dotSprite1->SetPosition(bb->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()),
		bb->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
	dotSprite2->SetPosition(bb->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()),
		bb->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
	dotSprite3->SetPosition(bb->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()),
		bb->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
	dotSprite4->SetPosition(bb->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()),
		bb->GetVertices()[3].y - (0.5f * dotSprite3->GetScaleHeight()));
}

void Engine::CookNCollect::Render()
{
	// Render all objects
	for (Ingredients* o : objects) {
		o->Draw();
	}
	for (Heart* o : hearts) {
		o->Draw();
	}
	basketSprite->Draw();
	scoreText->Draw();
	dot->Draw();

	dotSprite1->Draw();
	dotSprite2->Draw();
	dotSprite3->Draw();
	dotSprite4->Draw();
}

/*
* Helper method to create a custom sprite
*/
Engine::Sprite* Engine::CookNCollect::CreateSprite()
{
	return (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetNumXFrames(3)->SetNumYFrames(3)->SetScale(4);

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

string  Engine::CookNCollect::FormatScore(int score) {
	ostringstream oss;
	oss << std::setfill('0') << std::setw(7) << score;
	return oss.str();
}



