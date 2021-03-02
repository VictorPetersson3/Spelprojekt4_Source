#pragma once
#include <assert.h>
#include "CommonUtilities/InputManager.h"

class InputManager
{
public:
    static void Init();
    static void Destroy();
    static CommonUtilities::InputManager& GetInstance();
    static bool IsReady();
private:
    InputManager() = default;
    static CommonUtilities::InputManager* myInstance;
};
