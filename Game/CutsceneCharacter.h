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
	void Render();

private:
	std::unique_ptr<Tga2D::CSprite> mySprite;
	LinkString myName;

};

