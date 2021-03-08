#pragma once
#include "tga2d\sprite\sprite.h"
#include "Collider.h"

struct TerrainTile
{
	TerrainTile(Tga2D::CSprite aSprite, Collider aCollider)
	{
		mySprite = aSprite;
		myCollider = aCollider;
	}

	TerrainTile(Tga2D::CSprite aSprite)
	{
		mySprite = aSprite;
	}

	Tga2D::CSprite mySprite;
	Collider myCollider;
};