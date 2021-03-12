#pragma once
#include "tga2d\sprite\sprite.h"
#include "Collider.h"
#include <memory>

struct TerrainTile
{
	TerrainTile(std::shared_ptr<Tga2D::CSprite> aSprite,std::shared_ptr<Collider> aCollider)
	{
		mySprite = aSprite;
		myCollider = aCollider;
	}

	TerrainTile(std::shared_ptr<Tga2D::CSprite> aSprite)
	{
		mySprite = aSprite;
	}

	std::shared_ptr<Tga2D::CSprite> mySprite;
	std::shared_ptr<Collider> myCollider;
};