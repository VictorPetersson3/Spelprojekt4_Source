#pragma once
#include "CommonUtilities/Vector2.hpp"

class Camera
{
public:
	Camera();
	~Camera() = default;
	void Init(const CommonUtilities::Vector2f& aPos);
	void Update();
	void RenderSprite(const Tga2D::CSprite aSprite);

private:
	CommonUtilities::Vector2f myPosition;
	float myMovementSpeed;
};
