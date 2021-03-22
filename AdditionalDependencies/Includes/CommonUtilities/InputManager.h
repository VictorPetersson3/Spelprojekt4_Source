#pragma once
#include <dinput.h>
#include "Vector2.hpp"
#define IS_DOWN 0x80

// DirectInput keycodes "https://gist.github.com/tracend/912308"
// Mouse buttons goes from 0 - 8
// Make sure that you have added "dxguid.lib" and "dinput8.lib" to Additional Dependencies in properties


class InputManager
{
public:
	InputManager() = default;
	~InputManager();
	bool InitDevices(HWND& aHWD, HINSTANCE aHINSTACE, DWORD aBoardId, DWORD aMouseId);

	// Keyboard Input------------------------------------------------------------
	inline bool GetKey(const int aIndex) const
	{
		return (myKeyboardStates[myCurrent][aIndex] & IS_DOWN) != 0;
	}
	inline bool GetKeyUp(const int aIndex) const
	{
		return (myKeyboardStates[myCurrent][aIndex] & IS_DOWN) == 0
			&& (myKeyboardStates[!myCurrent][aIndex] & IS_DOWN) != 0;
	}
	inline bool GetKeyDown(const int aIndex) const
	{
		return (myKeyboardStates[myCurrent][aIndex] & IS_DOWN) != 0
			&& (myKeyboardStates[!myCurrent][aIndex] & IS_DOWN) == 0;
	}

	// Mouse input--------------------------------------------------------------
	inline bool GetMouseButton(const int aIndex) const
	{
		return (myMouseStates[myCurrent].rgbButtons[aIndex] & IS_DOWN);
	}
	inline bool GetMouseButtonDown(const int aIndex) const
	{
		return (myMouseStates[myCurrent].rgbButtons[aIndex] & IS_DOWN)
			&& !(myMouseStates[!myCurrent].rgbButtons[aIndex] & IS_DOWN);
	}
	inline bool GetMouseButtonUp(const int aIndex) const
	{
		return !(myMouseStates[myCurrent].rgbButtons[aIndex] & IS_DOWN)
			&& (myMouseStates[!myCurrent].rgbButtons[aIndex] & IS_DOWN);
	}
	// Mouse position------------------------------------------------------------
	inline CommonUtilities::Vector2f GetMousePositionRaw() const
	{
		return CommonUtilities::Vector2f(myMousePositionRawX, myMousePositionRawY);
	}
	inline  CommonUtilities::Vector2f GetMousePosition() const
	{
		return CommonUtilities::Vector2f(myMousePositionX, myMousePositionY);
	}

	inline void SetWindowSize(int aX, int aY)
	{
		myWindowSizeX = aX;
		myWindowSizeY = aY;
	}
	// Mouse delta------------------------------------------------------------
	inline CommonUtilities::Vector2f GetMouseDelta()
	{
		return CommonUtilities::Vector2f(myMouseStates[myCurrent].lX - myMouseStates[!myCurrent].lX, 
										 myMouseStates[myCurrent].lY - myMouseStates[!myCurrent].lY);
	}

	void Update();

private:

	bool InitMouse(HWND& aHWD, DWORD aMouseId);
	bool InitKeyboard(HWND& aHWD, DWORD aBoardId);
	void PullInput();

private:

	// Last / Current frame
	bool myCurrent = false;

	int myMousePositionX,
		myMousePositionY,
		myMousePositionRawX,
		myMousePositionRawY;

	int myWindowSizeX,
		myWindowSizeY;

	// Hanterar alla mina devices
	IDirectInput8* myInputDriver = nullptr;

	IDirectInputDevice8* myMouse = nullptr;
	IDirectInputDevice8* myKeyboard = nullptr;

	// Två states [0] => present, [1] => last
	DIMOUSESTATE2 myMouseStates[2];

	// 2 => detta statet och det förra
	// 256 => antal unika värden i en "char" 
	// Ett tangenttryck => "char";
	byte myKeyboardStates[2][256];

};

