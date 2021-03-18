#pragma once
#include "MenuObject.h"

class UIImage;
class ControllerLayOutState :
    public MenuObject
{
public:
    ControllerLayOutState() = default;
    ~ControllerLayOutState() = default;
    void Init(const EStateType& aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
private:
    void BackButtonPress();
    std::unique_ptr<UIImage> myBackground;
};

