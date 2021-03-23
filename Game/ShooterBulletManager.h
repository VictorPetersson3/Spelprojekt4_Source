#pragma once 
#include "Bullet.h"
#include <array>
#include "CommonUtilities/Vector2.hpp"

using Vector2 = CommonUtilities::Vector2f;

class ShooterBulletManager
{
public:
	void Update(float aDeltaTime);
	void Render();
	void CallBullet(Vector2 aPosition, Vector2 aDirection);
	 
private:
	std::array<Bullet, 50> myBullets;
};

