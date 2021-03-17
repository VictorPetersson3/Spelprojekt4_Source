#pragma once
#include "CommonUtilities/Vector2.hpp"

using Vector2 = CommonUtilities::Vector2f;

class Bullet
{
	Vector2 myDirection;

	static float mySpeed;
	static float myMaxLifetime;
	float myRemainingLifetime;
	bool myIsActive;	
};

