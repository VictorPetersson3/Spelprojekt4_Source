#pragma once
#include "tga2d\sprite\sprite.h"
#include "Collider.h"
#include <memory>
#include "RenderCommand.h"
struct TerrainTile
{
	TerrainTile(std::shared_ptr<Collider> aCollider, const RenderCommand& aRenderCommand)
	{
		myRenderCommand = aRenderCommand;
		myCollider = aCollider;
	}

	TerrainTile(const RenderCommand& aRenderCommand)
	{
		myRenderCommand = aRenderCommand;
		myCollider = std::make_shared<Collider>();
		myCollider->SetTag(EColliderTag::IgnoreCollision);
	}
	RenderCommand myRenderCommand;
	std::shared_ptr<Collider> myCollider;
};