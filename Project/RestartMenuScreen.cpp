#include "RestartMenuScreen.h"

Engine::RestartMenuScreen::RestartMenuScreen()
{
    text = NULL;
    bgSprite = NULL;
    textGameOver = NULL;
    finalScore = 0;
}

void Engine::RestartMenuScreen::Init()
{
    // Create background texture and sprite
    Texture* mainMenuTexture = new Texture("mainmenubutton.png");
    Texture* restartTexture = new Texture("restart.png");

    Texture* bgTexture = new Texture("background_restaurant.png");
    Texture* buttonTexture = new Texture("button_background_mainmenu.png");

    bgSprite = new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
    bgSprite->SetSize(game->GetSettings()->screenWidth, game->GetSettings()->screenHeight);

    // Create Restart Button
    Sprite* restartSprite = (new Sprite(restartTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
        ->SetNumXFrames(3)->SetScale(game->GetSettings()->screenWidth * 0.001953125)->SetNumYFrames(1)->AddAnimation("normal", 0, 0)->AddAnimation("hover", 0, 2)
        ->AddAnimation("press", 0, 2)->SetAnimationDuration(400);
    Button* restartButton = new Button(restartSprite, "restart");
    restartButton->SetPosition((game->GetSettings()->screenWidth / 2) - (restartSprite->GetScaleWidth() / 2), game->GetSettings()->screenHeight * 11 / 36);
    buttons.push_back(restartButton);

    // Create Exit Button
    Sprite* mainMenuSprite = (new Sprite(mainMenuTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
        ->SetNumXFrames(3)->SetScale(game->GetSettings()->screenWidth * 0.001953125)->SetNumYFrames(1)->AddAnimation("normal", 0, 0)->AddAnimation("hover", 0, 2)
        ->AddAnimation("press", 0, 2)->SetAnimationDuration(400);
    Button* mainMenuButton = new Button(mainMenuSprite, "mainmenu");
    mainMenuButton->SetPosition((game->GetSettings()->screenWidth / 2) - (mainMenuSprite->GetScaleWidth() / 2), restartButton->GetPosition().y - mainMenuSprite->GetScaleHeight() * 1.5);
    buttons.push_back(mainMenuButton);

    // Set active button
    currentButtonIndex = 0;
    buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

    // Create Text
    text = (new Text("8-bit Arcade In.ttf", 200, game->GetDefaultTextShader()))
        ->SetText("Game Over")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 400, game->GetSettings()->screenHeight - 200.0f)->SetColor(213, 168, 134);

    textGameOver = (new Text("greenscr.ttf", 30, game->GetDefaultTextShader()))
        ->SetText("Final Score: 0")  // Set teks awal
        ->SetPosition(game->GetSettings()->screenWidth * 0.5f - 200, game->GetSettings()->screenHeight - 150)
        ->SetColor(255, 255, 255);

    // Add input mappings
    game->GetInputManager()->AddInputMapping("next", SDLK_RIGHT)
        ->AddInputMapping("prev", SDLK_LEFT)
        ->AddInputMapping("press", SDLK_SPACE);
}

void Engine::RestartMenuScreen::Update()
{
    // Navigate through buttons
    if (game->GetInputManager()->IsKeyReleased("next")) {
        buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
        currentButtonIndex = (currentButtonIndex < (int)buttons.size() - 1) ? currentButtonIndex + 1 : currentButtonIndex;
        buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
    }

    if (game->GetInputManager()->IsKeyReleased("prev")) {
        buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
        currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
        buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
    }

    // Handle button press
    if (game->GetInputManager()->IsKeyReleased("press")) {
        Button* b = buttons[currentButtonIndex];
        b->SetButtonState(Engine::ButtonState::PRESS);

        if (b->GetButtonName() == "restart") {
            ScreenManager::GetInstance(game)->SetCurrentScreen("gameplay"); // Kembali ke ingame

            // Panggil metode RestartGame() pada instance dari GameScreen
            //MainMenuScreen* gameScreen = dynamic_cast<MainMenuScreen*>(ScreenManager::GetInstance(game)->GetCurrentScreen());
            GamePlayScreen* gameScreen = dynamic_cast<GamePlayScreen*>(ScreenManager::GetInstance(game)->GetCurrentScreen());
            if (gameScreen) {
                gameScreen->ResetGameState();
            }
        }
        else if (b->GetButtonName() == "mainmenu") {
            ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu"); // Kembali ke mainmenu
            MainMenuScreen* mainMenuScreen = dynamic_cast<MainMenuScreen*>(ScreenManager::GetInstance(game)->GetCurrentScreen()); 
        }
    }

    // Update buttons
    for (Button* b : buttons) {
        b->Update(game->GetGameTime());
    }
}

void Engine::RestartMenuScreen::Draw()
{
    bgSprite->Draw();

    for (Button* b : buttons) {
        b->Draw();
    }

    text->Draw();
    textGameOver->Draw();
}

void Engine::RestartMenuScreen::SetFinalScore(int finalScore) {
    std::string finalScoreText = "Final Score: " + std::to_string(finalScore);
    //textGameOver->SetScale(3.0f)->SetText("Game Over! Final Score: " + std::to_string(score))->SetPosition(game->GetSettings()->screenWidth * 0.5f - 500, game->GetSettings()->screenHeight - 500.0f)->SetColor(0, 0, 0);

    textGameOver->SetText(finalScoreText)->SetPosition(game->GetSettings()->screenWidth * 0.5f - 130, game->GetSettings()->screenHeight - 240.0f)->SetColor(213, 168, 134);
}