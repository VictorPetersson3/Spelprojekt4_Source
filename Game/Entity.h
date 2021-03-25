#pragma once
#include "RenderCommand.h"

class Entity
{
public:
	enum class EntityType
	{
		eSaw,
		eShooter,
		ePlayerStart,
		eLevelEnd
	};

	EntityType myEntityType;
	virtual void Update(float aDeltaTime) = 0;
	virtual void Render(const std::shared_ptr<Camera> aCamera) = 0;
};