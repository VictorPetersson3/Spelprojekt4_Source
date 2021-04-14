#include "stdafx.h"
#include "CutsceneData.h"
#include "UIImage.h"

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

void CutsceneData::AddAfterImage(const char* aImagePath)
{
	myHasAnAfterimage = true;
	myAfterImage = std::make_shared<UIImage>();
	myAfterImage->Init({0.5f, 0.5f}, aImagePath, 0);
	myAfterImage->GetRenderCommand().SetSizeRelativeToImage({ 0.5f, 0.5f });
	myAfterImage->Deactivate();
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

std::shared_ptr<UIImage> CutsceneData::GetAfterImage()
{
	if (myHasAnAfterimage)
	{
		return myAfterImage;
	}
	return nullptr;
}
