#pragma once

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
	virtual std::shared_ptr<Tga2D::CSpriteBatch> GetRenderSprite() = 0;
};