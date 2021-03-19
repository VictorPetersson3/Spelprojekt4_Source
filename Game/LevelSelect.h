#pragma once
#include "MenuObject.h"

class UIImage;
namespace Tga2D
{
    class CCustomShader;
}
class LevelSelect :
    public MenuObject
{
public:
    LevelSelect() = default;
    ~LevelSelect() = default;
    void Init(const EStateType & aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
private:
    void BackButtonPress();
    void MapMarkerPress(int aVal);

    float myCharacterMoveTimer;
    int myCharactersPreviousIndex;
    int myCharactersCurrentIndex;

    int myCurrentHoveredButtonVertical = 0;
    int myCurrentHoveredButtonHorizontal = 0;
    std::unique_ptr<UIImage> myBackground;
    std::unique_ptr<UIImage> myPanningBackground;
    std::unique_ptr<UIImage> myPlayerAvatar;

    std::shared_ptr<Tga2D::CCustomShader> myPanningShader;
};

