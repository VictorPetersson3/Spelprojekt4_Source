#pragma once
#include <iostream>
#include <vector>
#include <CommonUtilities/Vector2.hpp>
#include <memory>
#include "Collider.h"
#include "Entity.h"


class Camera;
class RenderCommand;
class AnimationClip;

using Vector2 = CommonUtilities::Vector2f;

class Saw : public Entity
{
public:

	Saw(Vector2 aStartPoint);
	void AddPoint(Vector2 aPoint);

	void Update(float aDeltatime) override;
	void Render(const std::shared_ptr<Camera> aCamera) override;
	void SetCollider(std::shared_ptr<Collider> aCollider);
	void SetRepeating(bool aRepeating);
	std::shared_ptr<Collider> myCollider;

private:

	std::shared_ptr<AnimationClip> myAnimationClip;
	std::vector<Vector2> myTravelPoints;
	int myNextPointIndex = 0;
	Vector2 myPosition;
	float myRadius = 0.5;
	float mySpeed = 0.1;
	int myDirection = 1;
	bool myRepeating = false;

	const float EPSILON = 0.01;
};

