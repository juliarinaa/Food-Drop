#include "MainMenuScreen.h"

Engine::MainMenuScreen::MainMenuScreen()
{
	textHighestScore = NULL;
	background = NULL;
	title = NULL;
}

void Engine::MainMenuScreen::Init()
{
	music = (new Music("Wobbly Adventure.ogg"))->SetVolume(60)->Play(true);
	// Create a Texture
	Texture* texture = new Texture("buttons.png");
	Texture* bgTexture = new Texture("background_restaurant.png");
	Texture* titleTexture = new Texture("title_mainmenu.png");
	//Texture* buttonTexture = new Texture("button_background_mainmenu.png");

	background = (new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);
	
	playSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(6)->SetScale(game->GetSettings()->screenWidth * 0.001953125)->SetNumYFrames(1)->AddAnimation("normal", 0, 0)->AddAnimation("hover", 0, 2)
		->AddAnimation("press", 0, 2)->SetAnimationDuration(400);

	Sprite* exitSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(6)->SetScale(game->GetSettings()->screenWidth * 0.001953125)->SetNumYFrames(1)->AddAnimation("normal", 3, 3)->AddAnimation("hover", 3, 5)
		->AddAnimation("press", 3, 5)->SetAnimationDuration(400);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((game->GetSettings()->screenWidth / 2) - (playSprite->GetScaleWidth() / 2), game->GetSettings()->screenHeight * 11 / 45);
	buttons.push_back(playButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2), playButton->GetPosition().y - exitSprite->GetScaleHeight() * 1.5);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Title
	title = new Sprite(titleTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	title->SetNumXFrames(2)->SetScale(game->GetSettings()->screenHeight * 0.00076388888 * 2.0f)->SetNumYFrames(1);
	title->SetPosition((game->GetSettings()->screenWidth - title->GetScaleWidth()) / 2.0f,(game->GetSettings()->screenHeight - title->GetScaleHeight()) / 0.8f);

	// Create Highest Score Text
	highestScore = LoadHighestScore();
	textHighestScore = (new Text("greenscr.ttf", static_cast<int>(round(game->GetSettings()->screenHeight * 0.04166666666)), game->GetDefaultTextShader()))->SetText("Highest Score: " + std::to_string(highestScore));  // Set teks awal
	textHighestScore->SetPosition((game->GetSettings()->screenWidth - textHighestScore->GetWidth()) / 2, playButton->GetPosition().y + playSprite->GetScaleHeight() + game->GetSettings()->screenHeight * 0.05)
		->SetColor(255, 255, 255);
	
	// Add input mappings
	game->GetInputManager()->AddInputMapping("next", SDLK_DOWN)
		->AddInputMapping("prev", SDLK_UP)
		->AddInputMapping("press", SDLK_RETURN);
}

void Engine::MainMenuScreen::Update()
{

	if (game->GetInputManager()->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = (currentButtonIndex < (int)buttons.size() - 1) ? currentButtonIndex + 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("play" == b->GetButtonName()) {
			music->Stop();
			ScreenManager::GetInstance(game)->SetCurrentScreen("gameplay");
			GamePlayScreen* gameScreen = dynamic_cast<GamePlayScreen*>(ScreenManager::GetInstance(game)->GetCurrentScreen());
			if(!firstTime){
				if (gameScreen) {
					gameScreen->ResetGameState();
				}
			}
			else { 
				gameScreen->SetHighestScore(highestScore);
				firstTime = false; 
			}
			gameScreen->PlayMusic();
			
		}
		else if ("exit" == b->GetButtonName()) {
			game->SetState(Engine::State::EXIT);
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}

}

void Engine::MainMenuScreen::Draw()
{
	background->Draw();
	title->Draw();
	//buttonBackground->Draw();

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	
	textHighestScore->Draw();
}

Engine::MainMenuScreen* Engine::MainMenuScreen::PlayMusic() {
	music->Play(true);
	return this;
}

Engine::MainMenuScreen* Engine::MainMenuScreen::SetHighestScore(int highestScore) {
	std::string HighestScoreText = "Highest Score: " + std::to_string(highestScore);
	textHighestScore->SetText(HighestScoreText);
	textHighestScore->SetPosition((game->GetSettings()->screenWidth - textHighestScore->GetWidth()) / 2, buttons[0]->GetPosition().y + playSprite->GetScaleHeight() + game->GetSettings()->screenHeight * 0.05);
	return this;
}

int Engine::MainMenuScreen::LoadHighestScore() {
	std::ifstream inFile("hs.dat", std::ios::binary);
	int score = 0;
	if (inFile.is_open()) {
		int encryptedScore;
		inFile.read(reinterpret_cast<char*>(&encryptedScore), sizeof(encryptedScore));
		score = encryptedScore ^ 0xA5;
		inFile.close();
	}
	return score;
}