#include "FoodDropGame.h"
#include "MainMenuScreen.h"
#include "GamePlayScreen.h"
#include "RestartMenuScreen.h"


Engine::FoodDropGame::FoodDropGame(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Food Drop";
}

Engine::FoodDropGame::~FoodDropGame()
{
}

void Engine::FoodDropGame::Init()
{
	Engine::ScreenManager::GetInstance(this)->AddScreen("gameplay", new GamePlayScreen())
		->AddScreen("mainmenu", new MainMenuScreen())->AddScreen("restartmenu", new RestartMenuScreen())
		->SetCurrentScreen("mainmenu");

}

void Engine::FoodDropGame::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();

}

void Engine::FoodDropGame::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}