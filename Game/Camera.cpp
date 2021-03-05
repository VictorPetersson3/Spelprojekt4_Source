#include "stdafx.h"
#include "Camera.h"
#include "Timer.h"
#include "InputManager.h"
#include "tga2d/sprite/sprite.h"
Camera::Camera()
{
	myMovementSpeed = 0.4f;
}

void Camera::Init(const CommonUtilities::Vector2f& aPos)
{
	myPosition = aPos;
}

//Here the logic for following the player will be
void Camera::Update(const CommonUtilities::Vector2f aPositionToFollow)
{
	/*if (InputManager::GetInstance().IsKeyDown('W'))
	{
		myPosition.y -= myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}*/
	if ( aPositionToFollow.x > myPosition.x + 0.5f)
	{
		myPosition.x += myMovementSpeed * Timer::GetInstance().GetDeltaTime();
		return;
	}
	else if (aPositionToFollow.x < myPosition.x + 0.5f)
	{
		myPosition.x -= myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}

	/*if (InputManager::GetInstance().IsKeyDown('S'))
	{
		myPosition.y += myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}*/
}

void Camera::RenderSprite(const Tga2D::CSprite aSprite)
{
	Tga2D::CSprite renderSprite = aSprite;
	CommonUtilities::Vector2f spritePos;
	spritePos.x = aSprite.GetPosition().x;
	spritePos.y = aSprite.GetPosition().y;
	spritePos -= myPosition;
	if (spritePos.x < 1.0f && spritePos.x > 0.0f && spritePos.y < 1.0f && spritePos.y > 0.0f)
	{
		renderSprite.SetPosition({ spritePos.x, spritePos.y });
		renderSprite.Render();
	}
}
