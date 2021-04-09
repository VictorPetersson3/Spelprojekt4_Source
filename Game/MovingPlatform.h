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


class MovingPlatform : public Entity
{
public:
	MovingPlatform(Vector2 aStartPoint);
	void AddPoint(Vector2 aPoint);

	void Update(float aDeltatime) override;
	void Render(const std::shared_ptr<Camera> aCamera) override;
	void SetCollider(std::shared_ptr<Collider> aCollider);
	void SetRepeating(bool aRepeating);
	void SetSize(Vector2 aRenderSize, float aGridSize);

private:
	std::shared_ptr<RenderCommand> myRenderCommand;
	std::vector<Vector2> myTravelPoints;
	int myNextPointIndex = 0;
	Vector2 myPosition;
	float myRadius = 0.5;
	float mySpeed = 0.1;
	int myDirection = 1;
	bool myRepeating = true;

	const float EPSILON = 0.01;
};

