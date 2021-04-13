#include "stdafx.h"
#include "CutsceneCharacter.h"
#include "tga2d/sprite/sprite.h"
#include "CommonUtilities/Math.h"
#include "Timer.h"

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
	myScaleTimer = 0;
	if (aState)
	{
		myGoalScale = 1;
	}
	else
	{
		myGoalScale = 0.8f;
	}
}

void CutsceneCharacter::MakeAngry(const bool aMood) { myIsAngry = aMood; }

void CutsceneCharacter::Update()
{
	myScaleTimer += Timer::GetInstance().GetDeltaTime() * 0.5;
	myCurrentScale = CommonUtilities::Lerp(myCurrentScale, myGoalScale, myScaleTimer);
	mySprite->SetSizeRelativeToImage({ myCurrentScale, myCurrentScale });
	myAngrySprite->SetSizeRelativeToImage({ myCurrentScale, myCurrentScale });
}

void CutsceneCharacter::Render()
{
	if (myIsAngry)
	{
		myAngrySprite->Render();
	}
	else
	{
		mySprite->Render();
	}
}

void CutsceneCharacter::SetPosition(const CommonUtilities::Vector2f& aPos)
{
	mySprite->SetPosition({aPos.x, aPos.y});
	myAngrySprite->SetPosition(mySprite->GetPosition());
}

void CutsceneCharacter::InitAngrySprite(const char* aImagePath)
{
	myAngrySprite = std::make_unique<Tga2D::CSprite>(aImagePath);
	myAngrySprite->SetPivot({ 0.5f, 0.5f });
	myAngrySprite->SetPosition(mySprite->GetPosition());
	SetActive(false);
}
