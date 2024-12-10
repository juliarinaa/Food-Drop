#include "GamePlayScreen.h"

Engine::GamePlayScreen::GamePlayScreen()
{

}

Engine::GamePlayScreen::~GamePlayScreen()
{
	delete texture;
	delete backgroundSprite;
	delete scoreBoardSprite;
	delete overlayBlackTexture;
	delete overlayBlackSprite;
	delete overlayWhiteTexture;
	delete overlayWhiteSprite;
	delete notesTexture;
	delete notesSprite;
	delete basketTexture;
	delete basketSprite;
	delete scoreTitle;
	delete scoreText;
	delete orderTitle;
	delete bonusScoreText;
	delete correctSound;
	delete wrongSound;
	delete completeSound;
	delete gameOverSound;
	delete music;
	delete currFood;
}

void Engine::GamePlayScreen::Init()
{
	srand(std::time(0));

	// Sound Effect
	correctSound = (new Sound("correct.wav"))->SetVolume(100);
	wrongSound = (new Sound("wrong.wav"))->SetVolume(100);
	completeSound = (new Sound("bonus point.wav"))->SetVolume(100);
	gameOverSound = (new Sound("gameover.wav"))->SetVolume(100);
	music = (new Music("00 lolurio - Everyday Life.ogg"))->SetVolume(70);

	// Basket
	texture = new Texture("basket.png");
	basketSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetScale(game->GetSettings()->screenWidth * 0.0001953125);
	basketSprite->SetPosition(game->GetSettings()->screenWidth / 2 - basketSprite->GetScaleWidth() / 2, 0);
	
	game->GetInputManager()->AddInputMapping("slide-left", SDLK_LEFT)->AddInputMapping("slide-right", SDLK_RIGHT);

	minXBasket = (game->GetSettings()->screenWidth / 3);
	maxXBasket = (game->GetSettings()->screenWidth * 2 / 3 - basketSprite->GetScaleWidth());

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
	game->SetBackgroundColor(201, 130, 130);

	//Set background (pict)
	Texture* bgTexture = new Texture("background_restaurant.png");
	backgroundSprite = (new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);

	//Set overlay black for background (pict)
	Texture* overlayBlackTexture = new Texture("overlay_black.png");
	overlayBlackSprite = (new Sprite(overlayBlackTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);

	//Set overlay white for background (pict)
	Texture* overlayWhiteTexture = new Texture("board.png");
	overlayWhiteSprite = (new Sprite(overlayWhiteTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize(game->GetSettings()->screenWidth * 22 / 60, game->GetSettings()->screenHeight);
	// Menentukan posisi X dan Y untuk meletakkan overlay di tengah layar
	float posX = (game->GetSettings()->screenWidth*19/60);  // Posisi X di tengah
	float posY = 0; // Posisi Y di tengah
	// Set posisi overlay
	overlayWhiteSprite->SetPosition(posX, posY);

	// Set notes for request
	Texture* notesTexture = new Texture("notes.png");
	notesSprite = (new Sprite(notesTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()));
	notesSprite->SetSize(game->GetSettings()->screenWidth * 9 / 60, notesSprite->GetScaleHeight() / notesSprite->GetScaleWidth() * game->GetSettings()->screenWidth * 9 / 60);
	//notesSprite->SetPosition(game->GetSettings()->screenWidth * 41 / 60 + (game->GetSettings()->screenWidth * 19 / 60 - notesSprite->GetScaleWidth()) / 2, (game->GetSettings()->screenHeight - notesSprite->GetScaleHeight()) / 2);
	notesSprite->SetPosition((game->GetSettings()->screenWidth * 19 / 60 - notesSprite->GetScaleWidth()) / 2, game->GetSettings()->screenHeight - notesSprite->GetScaleHeight());

	// Order text setting
	orderTitle = (new Text("ARCADECLASSIC.ttf", static_cast<int>(round(game->GetSettings()->screenWidth * 0.02109375)), game->GetDefaultTextShader()));
	orderTitle->SetText("order");
	orderTitle->SetColor(0, 0, 0)->SetPosition(notesSprite->GetPosition().x + (notesSprite->GetScaleWidth() - orderTitle->GetWidth())/ 2, game->GetSettings()->screenHeight - notesSprite->GetScaleHeight() / 3);
	fixOrderTitleY = orderTitle->GetPosition().y;
	
	// tekstur untuk checklist
	Texture* checklistTexture = new Texture("checklist.png");
	

	// Set request
	foodTypeAmount = (std::rand() % 3) + 1;
	for (size_t i = 1; i <= 3; i++)
	{
		/*Sprite* foodSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), defaultQuad))->SetNumXFrames(3)->SetNumYFrames(3)->SetScale(game->GetSettings()->screenWidth * 0.001953125)->SetPosition(notesSprite->GetPosition().x + notesSprite->GetScaleWidth() * 2 / 13, game->GetSettings()->screenHeight - notesSprite->GetScaleHeight() * (22 + i * 11) / 60);*/
		Sprite* foodSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetNumXFrames(3)->SetNumYFrames(3)->SetScale(game->GetSettings()->screenWidth * 0.001953125);
		foodSprite->SetPosition(notesSprite->GetPosition().x + notesSprite->GetScaleWidth() * 2 / 13, orderTitle->GetPosition().y - i * (foodSprite->GetScaleHeight() + notesSprite->GetScaleHeight() * 0.022) - notesSprite->GetScaleHeight() * 0.046);
		
		Sprite* checklistSprite = (new Sprite(checklistTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetScale(game->GetSettings()->screenWidth * 0.0000625);
		checklistSprite->SetPosition(foodSprite->GetPosition().x + notesSprite->GetScaleWidth() / 2, foodSprite->GetPosition().y + (foodSprite->GetScaleHeight() - checklistSprite->GetScaleHeight()) / 2);
		
		Text* amountText = (new Text("ARCADECLASSIC.ttf", static_cast<int>(round(game->GetSettings()->screenWidth * 0.01953125)), game->GetDefaultTextShader()))->SetColor(0, 0, 0);
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
	game->GetInputManager()->AddInputMapping("quit", SDLK_ESCAPE);

	//load heart texture
	texture = new Texture("heart.png");
	for (int i = 0; i < 3; i++) {
		Heart* o = new Heart((new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetNumXFrames(5)->SetNumYFrames(1)->AddAnimation("gone", 0, 4)->SetScale(game->GetSettings()->screenWidth * 0.001953125)->SetAnimationDuration(150));
		hearts.push_back(o);
	}

	// set heart position
	for (size_t i = 0; i < 3; i++)
	{
		hearts[i]->SetPosition(game->GetSettings()->screenWidth * 0.98 - (i + 1) * hearts[i]->GetWidth() - (i* game->GetSettings()->screenWidth * 0.0078125), game->GetSettings()->screenHeight * 0.96 - hearts[i]->GetHeight());
	}

	// Set Score Board
	Texture* scoreBoardTexture = new Texture("mini_notes.png");
	scoreBoardSprite = (new Sprite(scoreBoardTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetScale(game->GetSettings()->screenWidth * 0.00078125);
	scoreBoardSprite->SetPosition(game->GetSettings()->screenWidth * 41 / 60 + (game->GetSettings()->screenWidth * 19 / 60 - scoreBoardSprite->GetScaleWidth()) / 2, game->GetSettings()->screenHeight * 0.7 - scoreBoardSprite->GetScaleHeight());

	// Score title setting
	scoreTitle = new Text("ARCADECLASSIC.ttf", static_cast<int>(round(game->GetSettings()->screenWidth * 0.0234375)), game->GetDefaultTextShader());
	scoreTitle->SetText("SCORE");  // Menampilkan teks "SCORE"
	scoreTitle->SetColor(0, 0, 0)->SetPosition(scoreBoardSprite->GetPosition().x + (scoreBoardSprite->GetScaleWidth() - scoreTitle->GetWidth()) / 2, scoreBoardSprite->GetPosition().y + scoreBoardSprite->GetScaleHeight() * 0.55);

	// Score text setting
	scoreText = new Text("ARCADECLASSIC.ttf", game->GetSettings()->screenWidth * 0.03125, game->GetDefaultTextShader());
	scoreText->SetText("0000000");
	scoreText->SetColor(0, 0, 0)->SetPosition(scoreBoardSprite->GetPosition().x + (scoreBoardSprite->GetScaleWidth() - scoreText->GetWidth()) / 2, scoreTitle->GetPosition().y - scoreText->GetHeight() - game->GetSettings()->screenHeight * 0.03);

	// Bonus Score text setting
	bonusScoreText = new Text("ARCADECLASSIC.ttf", static_cast<int>(round(game->GetSettings()->screenWidth * 0.0234375)), game->GetDefaultTextShader());
	bonusScoreText->SetColor(106, 193, 97)->SetPosition(scoreBoardSprite->GetPosition().x + (scoreBoardSprite->GetScaleWidth() - bonusScoreText->GetWidth()) / 2, scoreBoardSprite->GetPosition().y + (scoreText->GetPosition().y - scoreBoardSprite->GetPosition().y - bonusScoreText->GetHeight()) / 2 + scoreBoardSprite->GetScaleHeight() * 0.02);
	
	currFood = SpawnObjects();
}

void Engine::GamePlayScreen::Update()
{
	// quit button
	if (game->GetInputManager()->IsKeyReleased("quit")) {
		game->SetState(Engine::State::EXIT);
	}

	if (!gameOver) {
		if(!allRequestFullfilled){
			// Spawn objects setelah objek terakhir mencapai ketinggian tertentu
			if (currFood->GetY() < game->GetSettings()->screenHeight * 0.75) {
				currFood = SpawnObjects();
			}

			// Update all objects
			for (Food* o : objects) {
				o->Update(game->GetGameTime(), foodVelocity);
			
				// detect coallision and update score
				// kalo misal si makanan itu berada di deket keranjang dan dia blm menghilang dari 
				// layar ataupun pernah ketangkap sebelumnya dan ada tabrakan dengan keranjang maka...
				if (o->GetY() <= basketSprite->GetScaleHeight()
					&& o->GetY() >= (basketSprite->GetScaleHeight() - game->GetGameTime() * foodVelocity - 1)
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
						if (hearts[0]->IsDie()) {
							music->Stop();
							gameOverSound->Play(false);
							if (highestScore < score) {
								highestScore = score;
								SaveHighestScore(score);
							}
							gameOver = true;
							// Mengganti ke layar restart menu saat game over
							ScreenManager::GetInstance(game)->SetCurrentScreen("restartmenu");
							// Kirim skor ke layar RestartMenuScreen
							RestartMenuScreen* restartMenu = dynamic_cast<RestartMenuScreen*>(ScreenManager::GetInstance(game)->GetCurrentScreen());
							if (restartMenu) {
								restartMenu->SetFinalScore(score);  // Set skor akhir sebelum berpindah layar
								restartMenu->SetHighestScore(highestScore);
							}
							return;
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
				notesY += yVelocity * game->GetGameTime();
				orderTitleY += yVelocity * game->GetGameTime();
				if (notesY >= game->GetSettings()->screenHeight) {
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
				notesY -= yVelocity * game->GetGameTime();
				orderTitleY -= yVelocity * game->GetGameTime();
				if (notesY <= game->GetSettings()->screenHeight - notesSprite->GetScaleHeight()) {
					allRequestFullfilled = false;
					moveUp = true;
					notesY = game->GetSettings()->screenHeight - notesSprite->GetScaleHeight();
					foodVelocity += 0.02f;
					basketVelocity += 0.01f;
					bonusScore = 0;
					currFood = SpawnObjects();
				} 
				if (orderTitleY < fixOrderTitleY) orderTitleY = fixOrderTitleY;
			}
			notesSprite->SetYPosition(notesY);
			orderTitle->SetYPosition(orderTitleY);
			for (Request* requestAsset : requestAssets) {
				requestAsset->Update(game->GetGameTime(), moveUp);
			}
		}

		for (Heart* o : hearts) {
			o->Update(game->GetGameTime());
		}

		// basket movement -> berdasarkan lesson 05
		float x = basketSprite->GetPosition().x;
		float y = basketSprite->GetPosition().y;
		// s = v * t;
		if (game->GetInputManager()->IsKeyPressed("slide-right")) {
			if (x <= maxXBasket) {
				x += basketVelocity * game->GetGameTime();
				basketSprite->SetPosition(x, y)->Update(game->GetGameTime());
			}
		}

		if (game->GetInputManager()->IsKeyPressed("slide-left")) {
			if (x >= minXBasket) {
				x -= basketVelocity * game->GetGameTime();
				basketSprite->SetPosition(x, y)->Update(game->GetGameTime());
			}
		}
	}
}

void Engine::GamePlayScreen::Draw()
{
	backgroundSprite->Draw();
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
		bonusScoreDuration -= game->GetGameTime();
		if(bonusScoreDuration <= 0){
			showBonusScore = false;
			bonusScoreDuration = 1000;
		}
	}

	for (Request* o : requestAssets) {
		o->Draw();
	}

	orderTitle->Draw();
}

/*
* Helper method to create a custom sprite
*/
Engine::Sprite* Engine::GamePlayScreen::CreateSprite()
{
	return (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetNumXFrames(3)->SetNumYFrames(3)->SetScale(game->GetSettings()->screenWidth * 0.003125);

}

Engine::GamePlayScreen* Engine::GamePlayScreen::PlayMusic()
{
	music->Play(true);
	return this;
}


Engine::Food* Engine::GamePlayScreen::SpawnObjects()
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
			int min = (int)(game->GetSettings()->screenWidth / 3);
			int max = (int)(game->GetSettings()->screenWidth * 2 / 3 - o->GetWidth());
			float x = (float)(rand() % (max - min + 1) + min);
			float y = game->GetSettings()->screenHeight + o->GetHeight();
			o->SetPosition(x, y);
			spawnCount++;
		}
	}
	return currFood;
}

string  Engine::GamePlayScreen::FormatScore(int score) {
	ostringstream oss;
	oss << std::setfill('0') << std::setw(7) << score;
	return oss.str();
}

void Engine::GamePlayScreen::ResetGameState() {
	music->Play(true);
	// Reset basket position
	basketSprite->SetPosition(game->GetSettings()->screenWidth / 2 - basketSprite->GetScaleWidth() / 2, 0);

	// Reset request dan makanan
	request.clear();
	unfulfilledRequest.clear();

	// Menghapus objek makanan yang ada
	for (Food* o : objects) {
		o->SetDie(); // Menghapus makanan yang ada
	}

	gameOver = false;
	foodVelocity = 0.2f;
	basketVelocity = 0.4f;
	allRequestFullfilled = false;
	moveUp = true;
	showBonusScore = false;
	bonusScoreDuration = 1000;
	score = 0;
	bonusScore = 0;

	for (Heart* h : hearts) {
		h->SetExist();
	}

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

	// Spawn makanan baru
	currFood = SpawnObjects();
	scoreText->SetText("0000000");
}

Engine::GamePlayScreen* Engine::GamePlayScreen::SetHighestScore(int score) {
	highestScore = score;
	return this;
}

void Engine::GamePlayScreen::SaveHighestScore(int score) {
	std::ofstream outFile("hs.dat", std::ios::binary);
	if (outFile.is_open()) {
		int encryptedScore = score ^ 0xA5;
		outFile.write(reinterpret_cast<const char*>(&encryptedScore), sizeof(encryptedScore));
		outFile.close();
	}
}