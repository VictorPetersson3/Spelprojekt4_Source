#pragma once
#include "MenuObject.h"

class UIImage;
class OptionsMenu :
    public MenuObject
{
public:
    OptionsMenu() = default;
    ~OptionsMenu() = default;
    void Init(const EStateType& aState) final;
    void Update() final;
    void Render() final;
private:
    void BackButtonPress();
    std::unique_ptr<UIImage> myBackground;
    int myCurrentHoveredButton = 0;

};

