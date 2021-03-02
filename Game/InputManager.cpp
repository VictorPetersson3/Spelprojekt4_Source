#include "stdafx.h"
#include "InputManager.h"
#include <assert.h>

CommonUtilities::InputManager* InputManager::myInstance = nullptr;

void InputManager::Init()
{
    assert(myInstance == nullptr && "Input Manager have already been Created");
    myInstance = new CommonUtilities::InputManager();
}

void InputManager::Destroy()
{
    assert(myInstance != nullptr && "Input Manager have already been destroyed");
    delete myInstance;
    myInstance = nullptr;
}

CommonUtilities::InputManager& InputManager::GetInstance()
{
    assert(myInstance != nullptr && "Input Manager is Nullptr");
    return *myInstance;
}

bool InputManager::IsReady()
{
    return myInstance != nullptr;
}
