#pragma once
#include <iostream>
#include <vector>
#include <CommonUtilities/Vector2.hpp>
#include <memory>
#include "RenderCommand.h"
#include "Collider.h"


class Camera;



using Vector2 = CommonUtilities::Vector2f;

class Saw
{
public:

	Saw(Vector2 aStartPoint);
	void AddPoint(Vector2 aPoint);

	void Update(float aDeltatime);
	void Render(const std::shared_ptr<Camera> aCamera);
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

