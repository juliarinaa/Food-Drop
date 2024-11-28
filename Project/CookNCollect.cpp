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

	//dot buat debugging aj
	/*dotTexture = new Texture("dot.png");
	dot = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);*/
	/*dot->SetPosition(setting->screenWidth / 2, basketSprite->GetScaleHeight())*/;

	/*dotSprite1 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite2 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite3 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite4 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);*/

	// Sound Effect
	correctSound = (new Sound("correct.wav"))->SetVolume(100);
	wrongSound = (new Sound("wrong.wav"))->SetVolume(100);
	completeSound = (new Sound("bonus point.wav"))->SetVolume(100);
	changeNoteSound = (new Sound("flipping2.wav"))->SetVolume(100);
	music = (new Music("00 lolurio - Everyday Life.ogg"))->SetVolume(70)->Play(true);

	// Basket
	texture = new Texture("basket.png");
	basketSprite = (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetScale(setting->screenWidth * 0.0001953125);
	basketSprite->SetPosition(setting->screenWidth / 2 - basketSprite->GetScaleWidth() / 2, 0);
	
	inputManager->AddInputMapping("slide-left", SDLK_LEFT)->AddInputMapping("slide-right", SDLK_RIGHT);

	minXBasket = (setting->screenWidth / 3);
	maxXBasket = (setting->screenWidth * 2 / 3 - basketSprite->GetScaleWidth());

	// Spawn setting
	maxSpawnTime = 1000;
	numObjectPerSpawn = 1;
	numObjectsInPool = 100;

	// Set food 
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

	// Set notes for request
	Texture* notesTexture = new Texture("notes.png");
	notesSprite = (new Sprite(notesTexture, defaultSpriteShader, defaultQuad));
	notesSprite->SetSize(setting->screenWidth * 9 / 60, notesSprite->GetScaleHeight() / notesSprite->GetScaleWidth() * setting->screenWidth * 9 / 60);
	//notesSprite->SetPosition(setting->screenWidth * 41 / 60 + (setting->screenWidth * 19 / 60 - notesSprite->GetScaleWidth()) / 2, (setting->screenHeight - notesSprite->GetScaleHeight()) / 2);
	notesSprite->SetPosition((setting->screenWidth * 19 / 60 - notesSprite->GetScaleWidth()) / 2, setting->screenHeight - notesSprite->GetScaleHeight());

	// Order text setting
	orderTitle = (new Text("ARCADECLASSIC.ttf", static_cast<int>(round(setting->screenWidth * 0.02109375)), defaultTextShader));
	orderTitle->SetText("order");
	orderTitle->SetColor(0, 0, 0)->SetPosition(notesSprite->GetPosition().x + (notesSprite->GetScaleWidth() - orderTitle->GetWidth())/ 2, setting->screenHeight - notesSprite->GetScaleHeight() / 3);
	fixOrderTitleY = orderTitle->GetPosition().y;
	
	// tekstur untuk checklist
	Texture* checklistTexture = new Texture("checklist.png");
	

	// Set request
	/*foodTypeAmount = (std::rand() % 3) + 1;*/
	foodTypeAmount = 3;
	for (size_t i = 1; i <= 3; i++)
	{
		/*Sprite* foodSprite = (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetNumXFrames(3)->SetNumYFrames(3)->SetScale(setting->screenWidth * 0.001953125)->SetPosition(notesSprite->GetPosition().x + notesSprite->GetScaleWidth() * 2 / 13, setting->screenHeight - notesSprite->GetScaleHeight() * (22 + i * 11) / 60);*/
		Sprite* foodSprite = (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetNumXFrames(3)->SetNumYFrames(3)->SetScale(setting->screenWidth * 0.001953125);
		foodSprite->SetPosition(notesSprite->GetPosition().x + notesSprite->GetScaleWidth() * 2 / 13, orderTitle->GetPosition().y - i * (foodSprite->GetScaleHeight() + notesSprite->GetScaleHeight() * 0.022) - notesSprite->GetScaleHeight() * 0.046);
		
		Sprite* checklistSprite = (new Sprite(checklistTexture, defaultSpriteShader, defaultQuad))->SetScale(setting->screenWidth * 0.0000625);
		checklistSprite->SetPosition(foodSprite->GetPosition().x + notesSprite->GetScaleWidth() / 2, foodSprite->GetPosition().y + (foodSprite->GetScaleHeight() - checklistSprite->GetScaleHeight()) / 2);
		
		Text* amountText = (new Text("ARCADECLASSIC.ttf", static_cast<int>(round(setting->screenWidth * 0.01953125)), defaultTextShader))->SetColor(0, 0, 0);
		amountText->SetPosition(foodSprite->GetPosition().x + notesSprite->GetScaleWidth() / 2, foodSprite->GetPosition().y + (foodSprite->GetScaleHeight() - amountText->GetHeight()) / 2);

		if (i <= foodTypeAmount) {
			int foodAmount = (std::rand() % 3) + 1;
			int frame = rand() % 9;
			// meriksa apakah makanannya yang dipilih itu udah ada sebelumnya dalam request
			while (request.count(frame) == 1) {
				frame = rand() % 9;
			}
			unfulfilledRequest.push_back(frame);
			foodSprite->SetFrame(frame);
			request.insert({ frame, foodAmount });
			requestAssets.push_back((new Request(foodSprite, checklistSprite, amountText))->SetAmount(foodAmount));
		}
		else {
			requestAssets.push_back(new Request(foodSprite, checklistSprite, amountText));
		}
	}

	// Add input
	inputManager->AddInputMapping("quit", SDLK_ESCAPE);

	//load heart texture
	texture = new Texture("heart.png");
	for (int i = 0; i < 3; i++) {
		Heart* o = new Heart((new Sprite(texture, defaultSpriteShader, defaultQuad))->SetNumXFrames(5)->SetNumYFrames(1)->AddAnimation("gone", 0, 4)->SetScale(setting->screenWidth * 0.001953125)->SetAnimationDuration(150));
		hearts.push_back(o);
	}

	// set heart position
	for (size_t i = 0; i < 3; i++)
	{
		hearts[i]->SetPosition(setting->screenWidth * 0.98 - (i + 1) * hearts[i]->GetWidth() - (i* setting->screenWidth * 0.0078125), setting->screenHeight * 0.96 - hearts[i]->GetHeight());
	}

	// Set Score Board
	Texture* scoreBoardTexture = new Texture("mini_notes.png");
	scoreBoardSprite = (new Sprite(scoreBoardTexture, defaultSpriteShader, defaultQuad))->SetScale(setting->screenWidth * 0.00078125);
	scoreBoardSprite->SetPosition(setting->screenWidth * 41 / 60 + (setting->screenWidth * 19 / 60 - scoreBoardSprite->GetScaleWidth()) / 2, setting->screenHeight * 0.7 - scoreBoardSprite->GetScaleHeight());

	// Score title setting
	scoreTitle = new Text("ARCADECLASSIC.ttf", setting->screenWidth * 0.0234375, defaultTextShader);
	scoreTitle->SetText("SCORE");  // Menampilkan teks "SCORE"
	scoreTitle->SetColor(0, 0, 0)->SetPosition(scoreBoardSprite->GetPosition().x + (scoreBoardSprite->GetScaleWidth() - scoreTitle->GetWidth()) / 2, scoreBoardSprite->GetPosition().y + scoreBoardSprite->GetScaleHeight() * 0.55);

	// Score text setting
	scoreText = new Text("ARCADECLASSIC.ttf", setting->screenWidth * 0.03125, defaultTextShader);
	scoreText->SetText("0000000");
	scoreText->SetColor(0, 0, 0)->SetPosition(scoreBoardSprite->GetPosition().x + (scoreBoardSprite->GetScaleWidth() - scoreText->GetWidth()) / 2, scoreTitle->GetPosition().y - scoreText->GetHeight() - setting->screenHeight * 0.03);

	// Bonus Score text setting
	bonusScoreText = new Text("ARCADECLASSIC.ttf", setting->screenWidth * 0.0234375, defaultTextShader);
	bonusScoreText->SetColor(106, 193, 97)->SetPosition(scoreBoardSprite->GetPosition().x + (scoreBoardSprite->GetScaleWidth() - bonusScoreText->GetWidth()) / 2, scoreText->GetPosition().y - bonusScoreText->GetHeight() - setting->screenHeight * 0.025);
	
	currFood = SpawnObjects();
}

void Engine::CookNCollect::Update()
{
	// quit button
	if (inputManager->IsKeyReleased("quit")) {
		state = Engine::State::EXIT;
	}

	if (!gameOver) {
		if(!allRequestFullfilled){
			// Spawn objects setelah objek terakhir mencapai ketinggian tertentu
			if (currFood->GetY() < setting->screenHeight * 0.75) {
				currFood = SpawnObjects();
			}

			// Update all objects
			for (Food* o : objects) {
				o->Update(GetGameTime(), foodVelocity);
			
				// detect coallision and update score
				// kalo misal si makanan itu berada di deket keranjang dan dia blm menghilang dari 
				// layar ataupun pernah ketangkap sebelumnya dan ada tabrakan dengan keranjang maka...
				if (o->GetY() <= basketSprite->GetScaleHeight()
					&& o->GetY() >= (basketSprite->GetScaleHeight() - GetGameTime() * foodVelocity - 1)
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
							score += 100;
							bonusScore += 50;
							scoreText->SetText(FormatScore(score));

							// Hapus dari request jika jumlahnya habis
							if (remainingAmount == 0) {
								request.erase(o->GetFrameIndex());
								requestAssets[i]->SetFullfilled();
								auto it = std::find(unfulfilledRequest.begin(), unfulfilledRequest.end(), o->GetFrameIndex());
								if (it != unfulfilledRequest.end()) unfulfilledRequest.erase(it);
								// kalo requestnya udah abis, food spawn-nya diilangin dari layar
								if (request.empty()) {
									completeSound->Play(false);
									allRequestFullfilled = true;
									for (Food* o : objects) o->SetDie();
									bonusScoreText->SetText("bonus " + std::to_string(bonusScore));
									bonusScoreText->SetXPosition(scoreBoardSprite->GetPosition().x + (scoreBoardSprite->GetScaleWidth() - bonusScoreText->GetWidth()) / 2);
									scoreText->SetText(FormatScore(score + bonusScore));
									showBonusScore = true;
									break;
								} 
							}
							correctSound->Play(false);
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
		}
		else {
			float notesY = notesSprite->GetPosition().y;
			float orderTitleY = orderTitle->GetPosition().y;
			float yVelocity = 0.2f;
			if (moveUp) {
				notesY += yVelocity * GetGameTime();
				orderTitleY += yVelocity * GetGameTime();
				if (notesY >= setting->screenHeight) {
					moveUp = false;
					foodTypeAmount = (std::rand() % 3) + 1;
					for (size_t i = 0; i < 3; i++)
					{
						if (i < foodTypeAmount) {
							int foodAmount = (std::rand() % 3) + 1;
							int frame = rand() % 9;
							// meriksa apakah makanannya yang dipilih itu udah ada sebelumnya dalam request
							while (request.count(frame) == 1) {
								frame = rand() % 9;
							}
							unfulfilledRequest.push_back(frame);
							requestAssets[i]->SetFoodFrame(frame)->SetAmount(foodAmount);
							request.insert({ frame, foodAmount });
						}
						else {
							requestAssets[i]->SetDie();
						}
					}
					//changeNoteSound->Play(false);
				}
			}
			else {
				notesY -= yVelocity * GetGameTime();
				orderTitleY -= yVelocity * GetGameTime();
				if (notesY <= setting->screenHeight - notesSprite->GetScaleHeight()) {
					allRequestFullfilled = false;
					moveUp = true;
					notesY = setting->screenHeight - notesSprite->GetScaleHeight();
					foodVelocity += 0.05f;
					bonusScore = 0;
					currFood = SpawnObjects();
				} 
				if (orderTitleY < fixOrderTitleY) orderTitleY = fixOrderTitleY;
			}
			notesSprite->SetYPosition(notesY);
			orderTitle->SetYPosition(orderTitleY);
			for (Request* requestAsset : requestAssets) {
				requestAsset->Update(GetGameTime(), moveUp);
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
	}

	////Shape for debug
	//BoundingBox* bb = objects[1]->GetBoundingBox();
	//dotSprite1->SetPosition(bb->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()),
	//	bb->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
	//dotSprite2->SetPosition(bb->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()),
	//	bb->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
	//dotSprite3->SetPosition(bb->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()),
	//	bb->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
	//dotSprite4->SetPosition(bb->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()),
	//	bb->GetVertices()[3].y - (0.5f * dotSprite3->GetScaleHeight()));
}

void Engine::CookNCollect::Render()
{
	backgroundSprite->Draw();
	//overlayBlackSprite->Draw();
	overlayWhiteSprite->Draw();
	notesSprite->Draw();
	scoreBoardSprite->Draw();

	if (!allRequestFullfilled) {
		for (Food* o : objects) {
			o->Draw();
		}
	}

	for (Heart* o : hearts) {
		o->Draw();
	}
	basketSprite->Draw();
	scoreTitle->Draw();
	scoreText->Draw();
	
	if (showBonusScore && bonusScoreDuration != 0) {
		bonusScoreText->Draw();
		bonusScoreDuration -= GetGameTime();
		if(bonusScoreDuration <= 0){
			showBonusScore = false;
			bonusScoreDuration = 1000;
		}
	}
	
	//dot->Draw();
	//dotSprite1->Draw();
	//dotSprite2->Draw();
	//dotSprite3->Draw();
	//dotSprite4->Draw();

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
	return (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetNumXFrames(3)->SetNumYFrames(3)->SetScale(setting->screenWidth * 0.003125);

}

Engine::Food* Engine::CookNCollect::SpawnObjects()
{
	//Find Die object to reuse for spawning
	Food* currFood = NULL;
	int spawnCount = 0;
	for (Food* o : objects) {
		if (spawnCount == numObjectPerSpawn) {
			break;
		}
		if (o->IsDie()) {
			// Set state to spawn
			o->SetSpawn();
			currFood = o;
			int frame = rand() % 17;
			if (frame % 2 != 0) frame = unfulfilledRequest[rand() % unfulfilledRequest.size()];
			else frame /= 2;
			o->SetFrame(frame);

			// Random spawn position
			int min = (int)(setting->screenWidth / 3);
			int max = (int)(setting->screenWidth * 2 / 3 - o->GetWidth());
			float x = (float)(rand() % (max - min + 1) + min);
			float y = setting->screenHeight + o->GetHeight();
			o->SetPosition(x, y);
			spawnCount++;
		}
	}
	return currFood;
}

string  Engine::CookNCollect::FormatScore(int score) {
	ostringstream oss;
	oss << std::setfill('0') << std::setw(7) << score;
	return oss.str();
}