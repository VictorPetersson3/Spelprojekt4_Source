#pragma once
#include "RenderCommand.h"

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
	virtual void Update(float aDeltaTime) = 0;
	virtual void Render(const std::shared_ptr<Camera> aCamera) = 0;
};