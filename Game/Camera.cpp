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
	myZoomFactor = 1;
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
		myZoomFactor += myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}

	if (InputManagerS::GetInstance().GetKey(DIK_K))
	{
		myZoomFactor -= myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}
}

void Camera::RenderSprite(Tga2D::CSprite aSprite)
{
	CommonUtilities::Vector2f spritePos;
	spritePos.x = aSprite.GetPosition().x;
	spritePos.y = aSprite.GetPosition().y;
	spritePos -= myPosition;
	if (spritePos.x < 1.20f && spritePos.x > -0.20f && spritePos.y < 1.20f && spritePos.y > -0.20f)
	{
		spritePos.x *= myZoomFactor;
		spritePos.y *= myZoomFactor;
		aSprite.SetSizeRelativeToImage({1 * myZoomFactor, 1 * myZoomFactor});
		aSprite.SetPosition({ spritePos.x, spritePos.y });
	}
}

void Camera::BatchRenderSprite(RenderCommand& aRenderCommand)
{
	CommonUtilities::Vector2f spritePos;
	spritePos.x = aRenderCommand.GetPosition().x - myPosition.x;
	spritePos.y = aRenderCommand.GetPosition().y - myPosition.y;
	if (spritePos.x < 1.20f && spritePos.x > -0.20f && spritePos.y < 1.20f && spritePos.y > -0.20f)
	{
		spritePos.x *= myZoomFactor;
		spritePos.y *= myZoomFactor;
		aRenderCommand.mySprite.get()->SetShouldRender(true);
		aRenderCommand.SetScaleFromCamera(myZoomFactor);
		aRenderCommand.SetSpritePosition(spritePos);
	}
	else
	{
		aRenderCommand.mySprite.get()->SetShouldRender(false);
	}
}

void Camera::RenderSprite(RenderCommand& aRenderCommand)
{
	CommonUtilities::Vector2f spritePos;
	spritePos.x = aRenderCommand.GetPosition().x - myPosition.x;
	spritePos.y = aRenderCommand.GetPosition().y - myPosition.y;
	if (aRenderCommand.myShouldBeCulled)
	{
		if (spritePos.x < 1.20f && spritePos.x > -0.20f && spritePos.y < 1.20f && spritePos.y > -0.20f)
		{
			spritePos.x *= myZoomFactor;
			spritePos.y *= myZoomFactor;
			aRenderCommand.SetScaleFromCamera(myZoomFactor);
			aRenderCommand.SetSpritePosition(spritePos);
			aRenderCommand.Render();
		}
	}
	else
	{
		aRenderCommand.SetSpritePosition(spritePos);
		aRenderCommand.Render();
	}
}
