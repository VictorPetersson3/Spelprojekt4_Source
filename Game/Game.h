#pragma once
#include <fstream>
#include "GameWorld.h"

class CGame
{
public:
	//CGame();
	CGame() : myGameWorld(&myInputManager, &myTimer) {}
	~CGame();
	bool Init(const std::wstring& aVersion = L"", HWND aHWND = nullptr);
private:
	void InitCallBack();
	void UpdateCallBack();
	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	CGameWorld myGameWorld;
	CommonUtilities::InputManager myInputManager;
	CommonUtilities::Timer myTimer;

};
