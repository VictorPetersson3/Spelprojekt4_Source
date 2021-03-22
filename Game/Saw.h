#pragma once
#include <iostream>
#include <vector>
#include <CommonUtilities/Vector2.hpp>
#include <memory>
#include "Collider.h"
#include "Entity.h"


class Camera;
class RenderCommand;

using Vector2 = CommonUtilities::Vector2f;

class Saw : public Entity
{
public:

	Saw(Vector2 aStartPoint);
	void AddPoint(Vector2 aPoint);

	void Update(float aDeltatime) override;
	void Render(const std::shared_ptr<Camera> aCamera) override;
	const std::shared_ptr<RenderCommand> GetRenderCommand() const;

	Collider myCollider;

private:

	std::shared_ptr<RenderCommand> myRenderCommand;
	std::vector<Vector2> myTravelPoints;
	int myNextPointIndex = 0;
	Vector2 myPosition;
	float myRadius;
	float mySpeed = 1;
	int myDirection = 1;

	const float EPSILON = 0.01;
};

