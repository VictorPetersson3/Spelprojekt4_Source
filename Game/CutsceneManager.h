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
    CutsceneManager(XController* aControllerPointer);
    ~CutsceneManager() = default;
    void Init(const EStateType & aState) final;
    void Init(const EStateType& aState, const char* aCutsceneDirectory);
    void Update() final;
    void Render() final;
    void OnPushed() final;
    void PlayCutscene(const int aLevelIndex, const bool aEndOfMapCutscene = false);
    void PlayLastCutscene();
    const int GetAmountOfConversations() const;
private:
    void LoadCharacters();
    void LoadCutscenes(const char* aCutsceneDirectory);
    void Dialogue();
    void ParseAndAddText();
    void ContinuePrint();
    void PrintEverything();
    void OnExit();
    

    unsigned int mySceneToPlay = -1;
    float myTextTimer = 0;
    bool myIsPrinting = false;
    bool myHasReachedEndOfSentence = false;
    bool myPrintEverything = false;
    bool myHasResumed = false;
    bool myPlayingEndCutscene = false;
    bool myHasAfterImageShown = false;

    unsigned int myCurrentLineIndexToPlay = 0;
    unsigned int myCurrentLetterInLineToPlay = 0;
    unsigned int myCurrentLineEnd = 0;

    std::string myCurrentLineToPlay;
    std::string myDialogueToRender;

    std::unique_ptr<UIImage> myBlackBackground;
    std::shared_ptr<UIImage> myAfterCutsceneImage;
    std::unique_ptr<UIImage> myTextBackgroundGradient;
    std::unique_ptr<UIImage> myTextBackground;

    std::shared_ptr<Tga2D::CText> myTextToPrint;
    std::shared_ptr<CutsceneCharacter> myLeftCharacter;
    std::shared_ptr<CutsceneCharacter> myRightCharacter;
    std::shared_ptr<CutsceneCharacter> myNullCharacter;

    CommonUtilities::GrowingArray < std::shared_ptr<CutsceneData> > myLevelCharacterDialogues;
    CommonUtilities::GrowingArray<std::shared_ptr<CutsceneCharacter>> myCharacters;
};

