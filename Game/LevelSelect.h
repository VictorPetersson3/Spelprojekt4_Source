#pragma once
#include "MenuObject.h"
#include "LinkString.h"

class LevelSelectLoadData;
class LevelSelect_SpecificLevelData;
class UIImage;
namespace Tga2D
{
    class CCustomShader;
}
class LevelSelect :
    public MenuObject
{
public:
    LevelSelect(XController* aControllerPointer) : MenuObject(aControllerPointer) {}
    ~LevelSelect() = default;
    void Init(const EStateType & aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
    void OnResumed() final;
    LevelSelect_SpecificLevelData* GetSpecificLevelData(const int aIndex) const;
    const int GetLevelAmount() const;
    const LinkString& GetWorldSong(const int aWorldIndex) const;

private:
    void LoadLevelButtons();
    void BackButtonPress();
    void MapMarkerPress(int aVal);

    float myCharacterMoveTimer = 0;
    int myCharactersPreviousIndex = 0;
    int myCharactersCurrentIndex = 0;

    int myCurrentHoveredButtonVertical = 0;
    int myCurrentHoveredButtonHorizontal = 0;
    std::unique_ptr<UIImage> myBackground;
    std::unique_ptr<UIImage> myPanningBackground;
    std::unique_ptr<UIImage> myPlayerAvatar;


    std::shared_ptr<Tga2D::CCustomShader> myPanningShader;

    std::shared_ptr < LevelSelectLoadData> myLevels_LevelData;
};

