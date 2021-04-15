#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Xinput.h>
#include <Windows.h>
#include <CommonUtilities/Vector2.hpp>

#pragma comment(lib, "XInput.lib")
class XController
{
public:
	XController(const int);
	XController(const int, const float);
	XINPUT_STATE GetControllerState();
	void Vibrate(float leftVib, float rightVib);
	bool IsConnected();

	void UpdateController();

	// Input Checks
	CommonUtilities::Vector2f GetLeftTumbStick();
	CommonUtilities::Vector2f GetRightTumbStick();
	CommonUtilities::Vector2f GetDPadInput();

	inline const bool IsButtonDown(const int aIndex)
	{
		return this->GetControllerState().Gamepad.wButtons & aIndex;
	}

	
	const bool IsButtonPressed(const int aIndex)
	{
		if (IsButtonDown(aIndex))
		{
			if (!myPressed)
			{
				myPressed = true;
				return true;
			}
		}
		return false;
	}

	// Basic buttons
	const bool IsButton_A_Pressed();
	const bool IsButton_B_Pressed();
	const bool IsButton_X_Pressed();
	const bool IsButton_Y_Pressed();


	// Shoulder buttons
	const bool IsButton_RS_Pressed();
	const bool IsButton_LS_Pressed();
	const bool IsButton_RT_Pressed();
	const bool IsButton_LT_Pressed();

	const bool IsButton_Start_Pressed();
	const bool IsButton_Back_Pressed();

private:

	// DPad buttons
	const bool IsDPadLeft_Pressed();
	const bool IsDPadRight_Pressed();
	const bool IsDPadUp_Pressed();
	const bool IsDPadDown_Pressed();

private:
	float myTimer = 0;
	float myTime = 1.f;
	bool myPressed = false;
	int myJoystickDeadZone = {};
	short myControllerNumber = {};
	XINPUT_STATE myControllerState;


};

