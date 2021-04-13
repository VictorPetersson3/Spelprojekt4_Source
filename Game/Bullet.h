#pragma once
#include "CommonUtilities/Vector2.hpp"
#include "Collider.h"
#include "RenderCommand.h"

using Vector2 = CommonUtilities::Vector2f;
class Camera;
class AnimationClip;

class Bullet
{
public:

	Bullet();

	void Call(Vector2 aPosition, Vector2 aDirection);
	void Return();
	bool GetActive();
	void Update(float aDeltaTime);
	void Render(std::shared_ptr<Camera> aCamera);
	std::shared_ptr<Collider> GetCollider();

private:

	std::shared_ptr<AnimationClip> myAnimationClip;
	Vector2 myPosition;
	Vector2 myDirection;
	std::shared_ptr<Collider> myCollider;
	float mySpeed = 0.0001f;
	float myMaxLifetime = 5;
	float mySize = 0.001;
	float myRemainingLifetime;
	bool myIsActive;	
	const float PI = 3.14159;

};

