#pragma once
#include <chrono>
namespace CommonUtilities
{
    class Timer
    {
    public:
        Timer()
        {
            myFrameStart = std::chrono::high_resolution_clock::now();
            myBegin = std::chrono::high_resolution_clock::now();

            myIsPaused = false;
            myPreviousSpeed = 0.0f;
            mySpeed = 1.0f;
        }
        Timer(const Timer& aTimer) = delete;
        Timer& operator=(const Timer& aTimer) = delete;
        void TUpdate();
        float TGetDeltaTime() const;
        double TGetTotalTime() const;

        void SetSpeed(float aSpeed);
        const float GetSpeed() const;
        void Freeze();
        void Resume();
        void ToggleFreeze();
        bool IsFrozen() const;

    private:
        float myDeltaTime = 0;
        std::chrono::time_point<std::chrono::high_resolution_clock> myFrameStart;
        std::chrono::time_point<std::chrono::high_resolution_clock> myBegin;

        // used in freezing, slow-mo, etc
        float mySpeed, myPreviousSpeed;
        bool myIsPaused;
    };
}