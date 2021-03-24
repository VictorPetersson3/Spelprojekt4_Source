#pragma once
#include "CommonUtilities/Vector2.hpp"
#include "Collider.h"

using Vector2 = CommonUtilities::Vector2f;

class Camera;
class RenderCommand;
class Bullet
{
public:

	Bullet();
	~Bullet() = default;

	void Call(Vector2 aPosition, Vector2 aDirection);
	void Return();
	bool GetActive();
	void Update(float aDeltaTime);
	void Render(std::shared_ptr<Camera> aCamera);

private:

	RenderCommand* myRenderCommand;
	Vector2 myPosition;
	Vector2 myDirection;
	Collider myCollider;
	float mySpeed = 1;
	float myMaxLifetime = 5;
	float mySize = 16;
	float myRemainingLifetime;
	bool myIsActive;	
};

