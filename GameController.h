#pragma once

#include "GameLevel.h"
#include "HPTimer.h"

class GameController
{
	GameController() {}

	static GameLevel* currentLevel;

	static HPTimer* hpTimer;

public:
	static bool Loading;

	static void Init();

	static void LoadInitialLevel(GameLevel* lev);
	static void SwitchLevel(GameLevel* lev);

	static void Render();
	static void Update();
	static void EventProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};