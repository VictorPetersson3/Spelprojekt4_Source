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

private:
	ECollider myType;

	float myRadius = 0;
	CommonUtilities::Vector2f mySize = { 0, 0 };
};

