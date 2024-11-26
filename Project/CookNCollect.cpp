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
	delete correctSound;
	delete wrongSound;
}

void Engine::CookNCollect::Init()
{
	srand(std::time(0));

	// Sound Effect
	correctSound = (new Sound("correct.wav"))->SetVolume(100);
	wrongSound = (new Sound("wrong.wav"))->SetVolume(100);
	music = (new Music("00 lolurio - Everyday Life.ogg"))->SetVolume(70)->Play(true);

	// Basket
	texture = new Texture("basket.png");
	basketSprite = (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetScale(0.25);
	basketSprite->SetPosition(setting->screenWidth / 2 - basketSprite->GetScaleWidth() / 2, 0);

	inputManager->AddInputMapping("slide-left", SDLK_LEFT)->AddInputMapping("slide-right", SDLK_RIGHT);

	minXBasket = (setting->screenWidth / 3);
	maxXBasket = (setting->screenWidth * 2 / 3 - basketSprite->GetScaleWidth());

	// dot buat debugging aj
	dotTexture = new Texture("dot.png");
	/*dot = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);*/
	//dot->SetPosition(50, 100);

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
		Food* o = new Food(CreateSprite());
		objects.push_back(o);
	}

	// Set background
	SetBackgroundColor(201, 130, 130);

	//Set background (pict)
	Texture* bgTexture = new Texture("background_restaurant.png");
	backgroundSprite = (new Sprite(bgTexture, defaultSpriteShader, defaultQuad))->SetSize((float)setting->screenWidth, (float)setting->screenHeight);

	//Set overlay black for background (pict)
	Texture* overlayBlackTexture = new Texture("overlay_black.png");
	overlayBlackSprite = (new Sprite(overlayBlackTexture, defaultSpriteShader, defaultQuad))->SetSize((float)setting->screenWidth, (float)setting->screenHeight);

	//Set overlay white for background (pict)
	Texture* overlayWhiteTexture = new Texture("board.png");
	overlayWhiteSprite = (new Sprite(overlayWhiteTexture, defaultSpriteShader, defaultQuad))->SetSize(setting->screenWidth*22/60, setting->screenHeight);
	// Menentukan posisi X dan Y untuk meletakkan overlay di tengah layar
	float posX = (setting->screenWidth*19/60);  // Posisi X di tengah
	float posY = 0; // Posisi Y di tengah
	// Set posisi overlay
	overlayWhiteSprite->SetPosition(posX, posY);

	//Set notes for request
	Texture* notesTexture = new Texture("notes.png");
	notesSprite = (new Sprite(notesTexture, defaultSpriteShader, defaultQuad));
	notesSprite->SetSize(setting->screenWidth * 9 / 60, notesSprite->GetScaleHeight() / notesSprite->GetScaleWidth() * setting->screenWidth * 9 / 60);
	//notesSprite->SetPosition(setting->screenWidth * 41 / 60 + (setting->screenWidth * 19 / 60 - notesSprite->GetScaleWidth()) / 2, (setting->screenHeight - notesSprite->GetScaleHeight()) / 2);
	notesSprite->SetPosition((setting->screenWidth * 19 / 60 - notesSprite->GetScaleWidth()) / 2, setting->screenHeight - notesSprite->GetScaleHeight());

	foodTypeAmount = (std::rand() % 3) + 1;

	// Order text setting
	orderTitle = (new Text("ARCADECLASSIC.ttf", 27, defaultTextShader));
	orderTitle->SetColor(0, 0, 0)->SetPosition(notesSprite->GetPosition().x + notesSprite->GetScaleWidth() / 3.5, setting->screenHeight - notesSprite->GetScaleHeight() / 3);
	orderTitle->SetText("Order");

	
	// tekstur untuk checklist
	Texture* checklistTexture = new Texture("checklist.png");
	
	// set request
	for (size_t i = 1; i <= foodTypeAmount; i++)
	{
		int foodAmount = (std::rand() % 9) + 1;
		int frame = rand() % 9;
		// meriksa apakah makanannya yang dipilih itu udah ada sebelumnya dalam request
		while(request.count(frame) == 1){
			frame = rand() % 9;
		}
		//Sprite* foodSprite = (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetNumXFrames(3)->SetNumYFrames(3)->SetScale(3)->SetFrame(frame)->SetPosition(notesSprite->GetPosition().x + notesSprite->GetScaleWidth() / 7, setting->screenHeight - notesSprite->GetScaleHeight() * (13 + i * 14) / 60);
		Sprite* foodSprite = (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetNumXFrames(3)->SetNumYFrames(3)->SetScale(2.5)->SetFrame(frame)->SetPosition(notesSprite->GetPosition().x + notesSprite->GetScaleWidth() * 2 / 13, setting->screenHeight - notesSprite->GetScaleHeight() * (22 + i * 11) / 60);
		Sprite* checklistSprite = (new Sprite(checklistTexture, defaultSpriteShader, defaultQuad))->SetScale(0.08)->SetPosition(foodSprite->GetPosition().x + notesSprite->GetScaleWidth() / 2, foodSprite->GetPosition().y + foodSprite->GetScaleHeight() / 6);
		Text* amountText = (new Text("ARCADECLASSIC.ttf", 25, defaultTextShader))->SetColor(0, 0, 0)->SetPosition(foodSprite->GetPosition().x + notesSprite->GetScaleWidth()/2, foodSprite->GetPosition().y + foodSprite->GetScaleHeight() / 3);
		unfulfilledRequest.push_back(frame);
		request.insert({frame, foodAmount});
		requestAssets.push_back((new Request(foodSprite, checklistSprite, amountText))->SetAmount(foodAmount));
	}

	// Add input
	inputManager->AddInputMapping("quit", SDLK_ESCAPE);

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

	// Score title setting
	scoreTitle = new Text("ARCADECLASSIC.ttf", 40, defaultTextShader);
	scoreTitle->SetColor(255, 255, 255)->SetPosition(setting->screenWidth - hearts[0]->GetWidth() - 100, setting->screenHeight * 9 / 12);
	scoreTitle->SetText("SCORE");  // Menampilkan teks "SCORE"

	// Score text setting
	scoreText = new Text("ARCADECLASSIC.ttf", 40, defaultTextShader);
	scoreText->SetColor(255, 255, 255)->SetPosition(setting->screenWidth - hearts[0]->GetWidth() - 145, setting->screenHeight *  25 / 36);
	scoreText->SetText("0000000");
}

void Engine::CookNCollect::Update()
{
	// quit button
	if (inputManager->IsKeyReleased("quit")) {
		state = Engine::State::EXIT;
	}

	if (!gameOver) {
		// Update all objects
		for (Food* o : objects) {
			o->Update(GetGameTime());
			
			// detect coallision and update score
			// kalo misal si makanan itu berada di deket keranjang dan dia blm menghilang dari 
			// layar ataupun pernah ketangkap sebelumnya dan ada tabrakan dengan keranjang maka...
			if (o->GetY() <= basketSprite->GetScaleHeight()
				&& o->GetY() >= (basketSprite->GetScaleHeight() - 5) 
				&& o->IsSpawn() 
				&& o->GetBoundingBox()->CollideWith(basketSprite->GetBoundingBox())) {
				
				// Cek apakah makanan ini sesuai dengan request
				if (request.count(o->GetFrameIndex()) > 0) {

					// Makanan sesuai permintaan
					int& remainingAmount = request[o->GetFrameIndex()];
					if (remainingAmount > 0) {
						remainingAmount--;
						int i = 0;
						for (; i < 3; i++)
						{
							if (requestAssets[i]->GetFoodFrameIndex() == o->GetFrameIndex()) {
								requestAssets[i]->SetAmount(remainingAmount);
								break;
							}
						}
						correctSound->Play(false);
						score += 100;
						scoreText->SetText(FormatScore(score));

						// Hapus dari request jika jumlahnya habis
						if (remainingAmount == 0) {
							request.erase(o->GetFrameIndex());
							requestAssets[i]->SetFullfilled();
						}
					}
				}
				else {
					// Makanan salah
					wrongSound->Play(false);
					for (int i = 2; i >= 0; i--) {
						if (hearts[i]->IsDie()) continue;
						hearts[i]->PlayAnim("gone")->SetDie();
						break;
					}
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
	backgroundSprite->Draw();
	//overlayBlackSprite->Draw();
	overlayWhiteSprite->Draw();
	notesSprite->Draw();

	// Render all objects
	for (Food* o : objects) {
		o->Draw();
	}
	for (Heart* o : hearts) {
		o->Draw();
	}
	basketSprite->Draw();
	scoreTitle->Draw();
	scoreText->Draw();
	
	// dot->Draw();

	dotSprite1->Draw();
	dotSprite2->Draw();
	dotSprite3->Draw();
	dotSprite4->Draw();

	for (Request* o : requestAssets) {
		o->Draw();
	}

	orderTitle->Draw();
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
	for (Food* o : objects) {
		if (spawnCount == numObjectPerSpawn) {
			break;
		}
		if (o->IsDie()) {
			// Set state to spawn
			o->SetSpawn();

			int frame = rand() % 20;
			if (frame % 2 != 0 || frame > 17) frame = requestAssets[rand() % requestAssets.size()]->GetFoodFrameIndex();
			else frame /= 2;
			o->SetFrame(frame);

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



