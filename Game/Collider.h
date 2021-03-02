#pragma once
#include "CommonUtilities/Vector2.hpp"

enum class ECollider
{
	Circle,
	AABB,
	LineVolume
};

class Collider
{
public:
	Collider(ECollider aColliderType = ECollider::Circle);
	~Collider();

	float GetRadius();
	CommonUtilities::Vector2f GetAABB();

private:
	ECollider myType;

	float myRadius = 0;
	CommonUtilities::Vector2f mySize = { 0, 0 };
	CommonUtilities::Vector2<CommonUtilities::Vector2f> myAABB = { { 0, 0 }, { 0, 0 } };

};

