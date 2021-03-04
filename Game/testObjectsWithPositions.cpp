#include "stdafx.h"
#include "testObjectsWithPositions.h"
#include "CommonUtilities/Random.h"
#include <tga2d/sprite/sprite.h>

#define CU CommonUtilities
#define CURandf CU::GetRandomFloat(0 , 1)
testObjectsWithPositions::testObjectsWithPositions()
{
	mySprite = std::make_unique<Tga2D::CSprite>("Sprites/NewCube.dds");
}
void testObjectsWithPositions::Init(const CU::Vector2f& aPos)
{
	mySprite->SetPosition({ aPos.x, aPos.y });
	mySprite->SetColor(Tga2D::CColor{ CURandf, CURandf, CURandf, 1 });
}

const std::unique_ptr<Tga2D::CSprite>& testObjectsWithPositions::GetSprite() const
{
	return mySprite;
}

