#pragma once
#include "LinkString.h"
#include "CommonUtilities/Vector2.hpp"

namespace Tga2D
{
	class CSprite;
}
class CutsceneCharacter
{
public:
	CutsceneCharacter(const char* aImagePath, const char* aName, const CommonUtilities::Vector2f& aPosition);
	const LinkString& GetName() const;
	void SetActive(const bool aState);
	void MakeAngry(const bool aMood);
	void Update();
	void Render();
	void SetPosition(const CommonUtilities::Vector2f& aPos);
	void InitAngrySprite(const char* aImagePath);

private:
	std::unique_ptr<Tga2D::CSprite> mySprite;
	std::unique_ptr<Tga2D::CSprite> myAngrySprite;
	bool myIsAngry = false;
	float myScaleTimer = 0;
	float myCurrentScale = 1;
	float myGoalScale = 0;
	LinkString myName;

};

