#include "MainMenuScreen.h"

Engine::MainMenuScreen::MainMenuScreen()
{
	text = NULL;
	background = NULL;
	title = NULL;
}

void Engine::MainMenuScreen::Init()
{
	// Create a Texture
	Texture* texture = new Texture("buttons.png");
	Texture* bgTexture = new Texture("cafe.png");
	Texture* titleTexture = new Texture("title.png");

	// Create Sprites
	background = (new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetPosition(0, 0);
	background->SetSize(game->GetSettings()->screenWidth, background->GetScaleHeight() / background->GetScaleWidth() * game->GetSettings()->screenWidth - 60);

	Sprite* playSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(6)->SetScale(3)->SetNumYFrames(1)->AddAnimation("normal", 0, 0)->AddAnimation("hover", 0, 2)
		->AddAnimation("press", 0, 2)->SetAnimationDuration(400);

	Sprite* exitSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(6)->SetScale(3)->SetNumYFrames(1)->AddAnimation("normal", 3, 3)->AddAnimation("hover", 3, 5)
		->AddAnimation("press", 3, 5)->SetAnimationDuration(400);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((game->GetSettings()->screenWidth / 2) - (playSprite->GetScaleWidth() / 2),
		350);
	buttons.push_back(playButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2),
		150);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Title
	title = new Sprite(titleTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	title->SetNumXFrames(1)->SetNumYFrames(1)->SetScale(0.8);
	title->SetPosition((game->GetSettings()->screenWidth - title->GetScaleWidth()) / 2.0f,(game->GetSettings()->screenHeight - title->GetScaleHeight()) / 0.8f);

	// Add input mappings
	game->GetInputManager()->AddInputMapping("next", SDLK_DOWN)
		->AddInputMapping("prev", SDLK_UP)
		->AddInputMapping("press", SDLK_RETURN);

}


void Engine::MainMenuScreen::Update()
{
	// Set background
	//game->SetBackgroundColor(52, 155, 235);

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
			ScreenManager::GetInstance(game)->SetCurrentScreen("fooddrop");
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

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}

}
