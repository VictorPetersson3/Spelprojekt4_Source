#pragma once
#include "MenuObject.h"

class UIImage;

class PauseMenu :
    public MenuObject
{
public:
    PauseMenu() = default;
    ~PauseMenu() = default;
    void Init(const EStateType & aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
private:
    void BackButtonPress();
    void PressGoToMainMenu();
    void PressSettingsButton();
    std::unique_ptr<UIImage> myBackground;
    int myCurrentHoveredButton = 0;
};

