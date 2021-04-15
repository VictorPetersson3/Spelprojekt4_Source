#pragma once
#include "MenuObject.h"

class UIImage;
class CreditsState :
    public MenuObject
{
public:
    CreditsState(XController* aControllerPointer) : MenuObject(aControllerPointer) {}
    ~CreditsState() = default;
    void Init(const EStateType & aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
private:
    void BackButtonPress();
    std::unique_ptr<UIImage> myBackground;
    std::unique_ptr<UIImage> myCredits;
};

