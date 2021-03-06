#pragma once
#include "RenderCommand.h"
#include "Collider.h"

class Camera;

class Entity
{
public:
	enum class EntityType
	{
		eSaw,
		eShooter,
		ePlayerStart,
		eLevelEnd,
		eMovingPlatform
	};

	EntityType myEntityType;
	std::shared_ptr<Collider> myCollider;

	virtual void Update(float aDeltaTime) = 0;
	virtual void Render(const std::shared_ptr<Camera> aCamera) = 0;
	virtual std::vector<std::shared_ptr<Collider>> GetAllColliders() = 0;
};