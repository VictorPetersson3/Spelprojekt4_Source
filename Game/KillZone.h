#pragma once
#include "Entity.h"

class Collider;

class KillZone : public Entity
{
public:

	KillZone(float aWidth, float aHeight,  CommonUtilities::Vector2f aPosition);
	~KillZone();

	void Update(float aDeltaTime) override;
	void Render(const std::shared_ptr<Camera> aCamera) override;

private:
	std::shared_ptr<Collider> myCollider;
};

