#pragma once
#include "MenuObject.h"

namespace Tga2D
{
    class CText;
}


class CutsceneCharacter;
class CutsceneData;
class UIImage;
class CutsceneManager :
    public MenuObject
{
public:
    CutsceneManager() = default;
    ~CutsceneManager() = default;
    void Init(const EStateType & aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
    void PlayCutscene(int aLevelIndex);
private:
    void LoadCharacters();
    void LoadCutscenes();
    void Dialogue();
    void ParseAndAddText();
    void ContinuePrint();
    void OnExit();
    

    unsigned int mySceneToPlay = -1;
    float myTextTimer = 0;
    bool myIsPrinting = false;
    bool myHasReachedEndOfSentence = false;
    bool myPrintEverything = false;

    unsigned int myCurrentLineIndexToPlay = 0;
    unsigned int myCurrentLetterInLineToPlay = 0;

    std::string myCurrentLineToPlay;
    std::string myDialogueToRender;

    std::unique_ptr<UIImage> myTextBackground;

    std::shared_ptr<Tga2D::CText> myTextToPrint;
    std::shared_ptr<CutsceneCharacter> myLeftCharacter;
    std::shared_ptr<CutsceneCharacter> myRightCharacter;

    CommonUtilities::GrowingArray < std::shared_ptr<CutsceneData> > myLevelCharacterDialogues;
    CommonUtilities::GrowingArray<std::shared_ptr<CutsceneCharacter>> myCharacters;
};
