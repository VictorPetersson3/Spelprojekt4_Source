#pragma once
#include "MenuObject.h"

class UIImage;
class AnimationClip;
namespace Tga2D
{
    class CText;
}
class CharacterSelectionScreen :
    public MenuObject
{
public:
    CharacterSelectionScreen() = default;
    ~CharacterSelectionScreen() = default;
    void Init(const EStateType & aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
    void UnlockNewWorld(EWorldLevel);
private:
    void CharacterChoicePress();
    void BackToLevelSelectPress();
    std::unique_ptr<UIImage> myBackground;
    std::unique_ptr<AnimationClip> myNormalCharacter;
    std::unique_ptr<AnimationClip> myGlideCharacter;
    std::unique_ptr<AnimationClip> myDoubleJumpCharacter;
    std::unique_ptr<Tga2D::CText> myCharacterDescription;
    std::unique_ptr<Tga2D::CText> myTitle; //This says please choose a character
    int myCurrentHoveredButton = 0;
    int myCurrentHoveredCharacter = 0;
    int myCurrentUnlockedWorld = 1;

    std::string myNormalCharacterDescription;
    std::string myNormalCharacterTitle;
    std::string myGlideCharacterDescription;
    std::string myGlideCharacterTitle;
    std::string myDoubleJumpCharacterDescription;
    std::string myDoubleJumpCharacterTitle;
};

