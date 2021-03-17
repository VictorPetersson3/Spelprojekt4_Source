#pragma once
#include "CommonUtilities/Vector2.hpp"
#include "Collider.h"

using Vector2 = CommonUtilities::Vector2f;

class RenderCommand;
class Bullet
{
public:

	Bullet();

	void Call(Vector2 aPosition, Vector2 aDirection);
	void Return();
	bool GetActive();
	void Update(float aDeltaTime);
	void Render();

private:

	std::unique_ptr<RenderCommand> myRenderCommand;
	Vector2 myPosition;
	Vector2 myDirection;
	Collider myCollider;
	static float mySpeed;
	static float myMaxLifetime;
	static float mySize;
	float myRemainingLifetime;
	bool myIsActive;	
};

