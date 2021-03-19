#pragma once
#include "MenuObject.h"

class UIImage;
class Level;

class EndOfLevelScreen :
    public MenuObject
{
public:
    EndOfLevelScreen(Level* aLevelPointer);
    ~EndOfLevelScreen() = default;
    void Init(const EStateType & aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
private:
    void NextLevelPress();
    void BackToMainButton();
    Level* myLevelPointer;
    std::unique_ptr<UIImage> myBackground;
    int myCurrentHoveredButton = 0;



};

