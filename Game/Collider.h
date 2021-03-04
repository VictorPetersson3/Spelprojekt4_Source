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
	Collider();
	Collider(float aRadius, CommonUtilities::Vector2f aPosition);
	Collider(CommonUtilities::Vector2f aPosition, float aWidth, float aHeight);
	//Collider(/*Line volumes och skit*/);

	void UpdateCollider(CommonUtilities::Vector2f anUpdatedPosition);

	void SetRadius(float aNewRadius);
	void SetAABB(AABB anAABB);
	void SetLowerLeft(CommonUtilities::Vector2f aPoint);
	void SetUpperRight(CommonUtilities::Vector2f aPoint);

	const void Draw() const;
	const float& GetRadius() const;
	const AABB& GetAABB() const;
	const CommonUtilities::Vector2f& GetSize() const;
	const CommonUtilities::Vector2f& GetPosition() const;
	const ECollider& GetType() const;

private:
	ECollider myType;

	float myRadius;

	CommonUtilities::Vector2f myPosition;
	AABB myAABB;
};

