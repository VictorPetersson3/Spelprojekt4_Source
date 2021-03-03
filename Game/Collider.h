#pragma once
#include "CommonUtilities/Vector2.hpp"

struct AABB
{
	CommonUtilities::Vector2f myLowerLeft = {};
	CommonUtilities::Vector2f myUpperRight = {};
	CommonUtilities::Vector2f mySize;
};

enum class ECollider
{
	Circle,
	AABB,
	LineVolume
};

class Collider
{
public:
	Collider(float aRadius, CommonUtilities::Vector2f aPosition);
	Collider(CommonUtilities::Vector2f aPointLowerLeft, float aWidth, float aHeight);
	//Collider(/*Line volumes och skit*/);

	void SetRadius(float aNewRadius);

	void SetAABB(AABB anAABB);
	void SetLowerLeft(CommonUtilities::Vector2f aPoint);
	void SetUpperRight(CommonUtilities::Vector2f aPoint);

	float GetRadius();
	AABB GetAABB();
	CommonUtilities::Vector2f GetSize();

private:
	ECollider myType;

	float myRadius;

	CommonUtilities::Vector2f myPosition;
	AABB myAABB;
};

