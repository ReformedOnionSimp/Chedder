#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::Loading;
HPTimer* GameController::hpTimer;

void GameController::Init()
{
	Loading = true;
	currentLevel = 0;
	hpTimer = new HPTimer();
}

void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true;
	lev->Loading = true;
	currentLevel = lev;
	currentLevel->Load();
	lev->Loading = false;
	Loading = false;
}

void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;
	lev->Loading = true;
	currentLevel->Unload();
	lev->Load();
	delete currentLevel;
	currentLevel = lev;
	Loading = false;
}

void GameController::Render()
{
	if (Loading)
		return;
	currentLevel->Render();
}

void GameController::Update()
{
	if (Loading)
		return;
	hpTimer->Update();
	currentLevel->Update(hpTimer->GetTimeDelta());
}

void GameController::EventProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (Loading)
		return;
	hpTimer->Update();
	currentLevel->EventProcess(uMsg, hwnd, hpTimer->GetTimeDelta());
}