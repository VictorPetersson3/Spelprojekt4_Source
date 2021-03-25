#include "stdafx.h"
#include "CutsceneCharacter.h"
#include "tga2d/sprite/sprite.h"

CutsceneCharacter::CutsceneCharacter(const char* aImagePath, const char* aName, const CommonUtilities::Vector2f& aPosition) : myName(aName)
{
	mySprite = std::make_unique<Tga2D::CSprite>(aImagePath);
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetPosition({ aPosition.x, aPosition.y });
	SetActive(false);
}

const LinkString& CutsceneCharacter::GetName() const
{
	return myName;
}

void CutsceneCharacter::SetActive(const bool aState)
{
	if (aState)
	{
		mySprite->SetSizeRelativeToImage({ 1.0f, 1.0f });
	}
	else
	{
		mySprite->SetSizeRelativeToImage({ 0.8f, 0.8f });
	}
}

void CutsceneCharacter::Render()
{
	mySprite->Render();
}

void CutsceneCharacter::SetPosition(const CommonUtilities::Vector2f& aPos)
{
	mySprite->SetPosition({aPos.x, aPos.y});
}
