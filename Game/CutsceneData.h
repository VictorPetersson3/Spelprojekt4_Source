#pragma once
#include "CommonUtilities/GrowingArray.hpp"

class CutsceneCharacter;
class UIImage;
struct CutsceneData
{
	CutsceneData();
	void AddLeftCharacter(std::shared_ptr<CutsceneCharacter> aCharacter);
	void AddRightCharacter(std::shared_ptr<CutsceneCharacter> aCharacter);
	void AddLine(std::pair<std::string, std::shared_ptr<CutsceneCharacter>>& aLine);
	void AddCharacterMood(const std::string& aMood);
	void AddAfterImage(const char* aImagePath);

	const CommonUtilities::GrowingArray<std::pair<std::string, std::shared_ptr<CutsceneCharacter>>>& GetLines();
	const CommonUtilities::GrowingArray<std::string>& GetCharacterMoods() const;
	std::shared_ptr<CutsceneCharacter> GetLeftCharacter();
	std::shared_ptr<CutsceneCharacter> GetRightCharacter();
	std::shared_ptr<UIImage> GetAfterImage();

private:
	CommonUtilities::GrowingArray<std::pair<std::string, std::shared_ptr<CutsceneCharacter>>> myLines;
	CommonUtilities::GrowingArray<std::string> myCharacterMoods;
	std::shared_ptr<CutsceneCharacter> myLeftCharacter;
	std::shared_ptr<CutsceneCharacter> myRightCharacter;
	std::shared_ptr<UIImage> myAfterImage;
	bool myHasAnAfterimage = false;
};

