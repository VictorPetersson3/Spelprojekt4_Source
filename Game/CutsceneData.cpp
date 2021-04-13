#include "stdafx.h"
#include "CutsceneData.h"

CutsceneData::CutsceneData()
{
	myLines.Init(6);
	myCharacterMoods.Init(6);
}

void CutsceneData::AddLeftCharacter(std::shared_ptr<CutsceneCharacter> aCharacter)
{
	myLeftCharacter = aCharacter;
}

void CutsceneData::AddRightCharacter(std::shared_ptr<CutsceneCharacter> aCharacter)
{
	myRightCharacter = aCharacter;
}

void CutsceneData::AddLine(std::pair<std::string, std::shared_ptr<CutsceneCharacter>>& aLine)
{
	myLines.Add(aLine);
}

void CutsceneData::AddCharacterMood(const std::string& aMood)
{
	myCharacterMoods.Add(aMood);
}

const CommonUtilities::GrowingArray<std::pair<std::string, std::shared_ptr<CutsceneCharacter>>>& CutsceneData::GetLines()
{
	return myLines;
}

const CommonUtilities::GrowingArray<std::string>& CutsceneData::GetCharacterMoods() const
{
	return myCharacterMoods;
}

std::shared_ptr<CutsceneCharacter> CutsceneData::GetLeftCharacter()
{
	return myLeftCharacter;
}

std::shared_ptr<CutsceneCharacter> CutsceneData::GetRightCharacter()
{
	return myRightCharacter;
}
