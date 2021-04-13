#pragma once
#include "CommonUtilities/GrowingArray.hpp"

class CutsceneCharacter;
struct CutsceneData
{
	CutsceneData();
	void AddLeftCharacter(std::shared_ptr<CutsceneCharacter> aCharacter);
	void AddRightCharacter(std::shared_ptr<CutsceneCharacter> aCharacter);
	void AddLine(std::pair<std::string, std::shared_ptr<CutsceneCharacter>>& aLine);
	void AddCharacterMood(const std::string& aMood);

	const CommonUtilities::GrowingArray<std::pair<std::string, std::shared_ptr<CutsceneCharacter>>>& GetLines();
	const CommonUtilities::GrowingArray<std::string>& GetCharacterMoods() const;
	std::shared_ptr<CutsceneCharacter> GetLeftCharacter();
	std::shared_ptr<CutsceneCharacter> GetRightCharacter();

private:
	CommonUtilities::GrowingArray<std::pair<std::string, std::shared_ptr<CutsceneCharacter>>> myLines;
	CommonUtilities::GrowingArray<std::string> myCharacterMoods;
	std::shared_ptr<CutsceneCharacter> myLeftCharacter;
	std::shared_ptr<CutsceneCharacter> myRightCharacter;
};

