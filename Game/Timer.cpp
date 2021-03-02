#include "stdafx.h"
#include "Timer.h"
#include <assert.h>
CommonUtilities::Timer* Timer::myInstance = nullptr;

void Timer::Init()
{
    assert(myInstance == nullptr && "Input Manager have already been Created");
    myInstance = new CommonUtilities::Timer();
}

void Timer::Destroy()
{
    assert(myInstance != nullptr && "Input Manager have already been destroyed");
    delete myInstance;
    myInstance = nullptr;
}

CommonUtilities::Timer& Timer::GetInstance()
{
    assert(myInstance != nullptr && "Input Manager is Nullptr");
    return *myInstance;
}

bool Timer::IsReady()
{
    return myInstance != nullptr;
}
