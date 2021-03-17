#include "stdafx.h"
#include "XController.h"

XController::XController(const int aPlayerNumber)
{
    myControllerNumber = aPlayerNumber - 1;
    myJoystickDeadZone = 32767 * 0.1f;
}

XController::XController(const int aPlayerNumber, const float aDeadZoneProcent)
{
    myControllerNumber = aPlayerNumber - 1;
    const float aMinDeadZone = 0.1f;
    if (aDeadZoneProcent > aMinDeadZone && aDeadZoneProcent < 1)
    {
        myJoystickDeadZone = 32767 * aDeadZoneProcent;
    }
    else 
    {
        myJoystickDeadZone = 32767 * aMinDeadZone;
    }
}

XINPUT_STATE XController::GetControllerState()
{
    ZeroMemory(&myControllerState, sizeof(XINPUT_STATE));
    XInputGetState(myControllerNumber, &myControllerState);
    return myControllerState;
}

bool XController::IsConnected()
{
    ZeroMemory(&myControllerState, sizeof(XINPUT_STATE));
    DWORD result = XInputGetState(myControllerNumber, &myControllerState);
    if (result == ERROR_SUCCESS) return true;
    
    return false;
}

// max value for vibration is "1" where min is "0";
void XController::Vibrate(float leftVib, float rightVib)
{
    XINPUT_VIBRATION vibration;
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

    
    if (leftVib > 1) leftVib = 1;
    if (rightVib > 1) rightVib = 1;
    

    vibration.wLeftMotorSpeed = leftVib * 65535;
    vibration.wRightMotorSpeed = rightVib * 65535;
    XInputSetState(myControllerNumber, &vibration);
}

CommonUtilities::Vector2f XController::GetLeftTumbStick()
{
    const int x = this->GetControllerState().Gamepad.sThumbLX;
    const int y = this->GetControllerState().Gamepad.sThumbLY;
   
    if (std::abs(x) > myJoystickDeadZone && std::abs(y) > myJoystickDeadZone) return CommonUtilities::Vector2f(x, y).GetNormalized();

    if (std::abs(y) > myJoystickDeadZone) return CommonUtilities::Vector2f(0, y / 32767);
    if (std::abs(x) > myJoystickDeadZone) return CommonUtilities::Vector2f(x / 32767, 0);
    
    return CommonUtilities::Vector2f::Zero();
}

CommonUtilities::Vector2f XController::GetRightTumbStick()
{
    const int x = this->GetControllerState().Gamepad.sThumbRX;
    const int y = this->GetControllerState().Gamepad.sThumbRY;
  
    if (std::abs(x) > myJoystickDeadZone && std::abs(y) > myJoystickDeadZone) return CommonUtilities::Vector2f(x, y).GetNormalized();  
   
    if (std::abs(y) > myJoystickDeadZone) return CommonUtilities::Vector2f(0, y / 32767); 
    if (std::abs(x) > myJoystickDeadZone) return CommonUtilities::Vector2f(x / 32767, 0);

    return CommonUtilities::Vector2f::Zero();
}

const bool XController::IsButton_A_Pressed()
{
    return this->GetControllerState().Gamepad.wButtons & XINPUT_GAMEPAD_A;
}

const bool XController::IsButton_B_Pressed()
{
    return this->GetControllerState().Gamepad.wButtons & XINPUT_GAMEPAD_B;
}

const bool XController::IsButton_X_Pressed()
{
    return this->GetControllerState().Gamepad.wButtons & XINPUT_GAMEPAD_X;
}

const bool XController::IsButton_Y_Pressed()
{
    return this->GetControllerState().Gamepad.wButtons & XINPUT_GAMEPAD_Y;
}

CommonUtilities::Vector2f XController::GetDPadInput()
{
    const int x = -IsDPadLeft_Pressed() + IsDPadRight_Pressed();
    const int y = -IsDPadDown_Pressed() + IsDPadUp_Pressed();
    return CommonUtilities::Vector2f(x, y);
}                                    

const bool XController::IsDPadLeft_Pressed()
{
    return this->GetControllerState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
}

const bool XController::IsDPadRight_Pressed()
{
    return this->GetControllerState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
}

const bool XController::IsDPadUp_Pressed()
{
    return this->GetControllerState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
}

const bool XController::IsDPadDown_Pressed()
{
    return this->GetControllerState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
}
