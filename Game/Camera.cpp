#include "stdafx.h"
#include "Camera.h"
#include "Timer.h"
#include "InputManager.h"
#include "tga2d/sprite/sprite.h"
#include "RenderCommand.h"

Camera::Camera()
{
	myPosition.Zero;
	myMovementSpeed = 0.15f;
}

void Camera::Init(const CommonUtilities::Vector2f& aPos)
{
	myPosition = aPos;
}

//Here the logic for following the player will be or whatever we will follow or the rules we have
void Camera::Update(const CommonUtilities::Vector2f aPositionToFollow)
{
	if (InputManagerS::GetInstance().GetKey(DIK_I))
	{
		myPosition.y -= myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}
	if (InputManagerS::GetInstance().GetKey(DIK_L))
	{
		myPosition.x += myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}
	if (InputManagerS::GetInstance().GetKey(DIK_J))
	{
		myPosition.x -= myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}
	if (InputManagerS::GetInstance().GetKey(DIK_K))
	{
		myPosition.y += myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}
	//printf("CameraPos x: %f y: %f\n", myPosition.x, myPosition.y);
}

void Camera::RenderSprite(Tga2D::CSprite aSprite)
{
	CommonUtilities::Vector2f spritePos;
	spritePos.x = aSprite.GetPosition().x;
	spritePos.y = aSprite.GetPosition().y;
	spritePos -= myPosition;
	if (spritePos.x < 1.0f && spritePos.x > 0.0f && spritePos.y < 1.0f && spritePos.y > 0.0f)
	{
		aSprite.SetPosition({ spritePos.x, spritePos.y });
	}
}

void Camera::BatchRenderSprite(RenderCommand& aRenderCommand)
{
	CommonUtilities::Vector2f spritePos;	
	spritePos.x = aRenderCommand.GetPosition().x - myPosition.x;
	spritePos.y = aRenderCommand.GetPosition().y - myPosition.y;
	if (spritePos.x < 1.0f && spritePos.x > 0.0f && spritePos.y < 1.0f && spritePos.y > 0.0f)
	{
		aRenderCommand.SetSpritePosition(spritePos);
	}
}

void Camera::RenderSprite(RenderCommand& aRenderCommand)
{
	CommonUtilities::Vector2f spritePos;
	spritePos.x = aRenderCommand.GetPosition().x - myPosition.x;
	spritePos.y = aRenderCommand.GetPosition().y - myPosition.y;
	if (spritePos.x < 1.0f && spritePos.x > 0.0f && spritePos.y < 1.0f && spritePos.y > 0.0f)
	{
		aRenderCommand.SetSpritePosition(spritePos);
		aRenderCommand.Render();
	}
}
