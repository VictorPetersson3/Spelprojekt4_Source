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
	XController(const int , const float);
	XINPUT_STATE GetControllerState();	
	void Vibrate(float leftVib, float rightVib);
	bool IsConnected();
	
	// Input Checks
	CommonUtilities::Vector2f GetLeftTumbStick();
	CommonUtilities::Vector2f GetRightTumbStick();
	CommonUtilities::Vector2f GetDPadInput();

	// Basic buttons
	const bool IsButton_A_Pressed();
	const bool IsButton_B_Pressed();
	const bool IsButton_X_Pressed();
	const bool IsButton_Y_Pressed();



private:
	
	// DPad buttons
	const bool IsDPadLeft_Pressed();
	const bool IsDPadRight_Pressed();
	const bool IsDPadUp_Pressed();
	const bool IsDPadDown_Pressed();

private:

	int myJoystickDeadZone = {};
	short myControllerNumber = {};
	XINPUT_STATE myControllerState;
	

};

