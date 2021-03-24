#pragma once
#include "CommonUtilities/InputManager.h"

class InputManagerS
{
public:
    static void Init();
    static void Destroy();
    static InputManager& GetInstance();
    static bool IsReady();
private:
    InputManagerS() = default;
    static InputManager* myInstance;
};
