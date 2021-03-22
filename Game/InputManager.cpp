#include "stdafx.h"
#include "InputManager.h"
#include <assert.h>

InputManager* InputManagerS::myInstance = nullptr;

void InputManagerS::Init()
{
    assert(myInstance == nullptr && "Input Manager have already been Created");
    myInstance = new InputManager();
}

void InputManagerS::Destroy()
{
    assert(myInstance != nullptr && "Input Manager have already been destroyed");
    delete myInstance;
    myInstance = nullptr;
}

InputManager& InputManagerS::GetInstance()
{
    assert(myInstance != nullptr && "Input Manager is Nullptr");
    return *myInstance;
}

bool InputManagerS::IsReady()
{
    return myInstance != nullptr;
}
