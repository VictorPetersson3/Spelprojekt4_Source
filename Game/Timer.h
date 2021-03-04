#pragma once
#include "CommonUtilities/Timer.h"

class Timer
{
public:
    static void Init();
    static void Destroy();
    static CommonUtilities::Timer& GetInstance();
    static bool IsReady();
private:
    Timer() = default;
    static CommonUtilities::Timer* myInstance;

};

