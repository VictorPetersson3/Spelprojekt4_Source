#pragma once
#include <iostream>
#include <vector>
#include <CommonUtilities/Vector2.hpp>
#include <memory>
#include "tga2d\sprite\sprite.h"
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

private:

	Tga2D::CSprite mySprite;
	Collider myCollider;
	std::vector<Vector2> myTravelPoints;
	int myNextPointIndex = 0;
	Vector2 myPosition;
	float myRadius;
	float mySpeed;
	int myDirection = 1;

	const float EPSILON = 0.000001f;
};

