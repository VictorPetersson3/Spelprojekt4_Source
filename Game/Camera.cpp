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
		myPosition *= myZoomFactor;
	}

	if (InputManagerS::GetInstance().GetKey(DIK_K))
	{
		myZoomFactor -= myMovementSpeed * Timer::GetInstance().GetDeltaTime();
		myPosition *= myZoomFactor;
	}
}

void Camera::RenderSprite(Tga2D::CSprite aSprite)
{
	const float boundMax = 1.20f / myZoomFactor;
	const float boundMin = -0.20f / myZoomFactor;
	CommonUtilities::Vector2f spritePos;
	spritePos.x = aSprite.GetPosition().x;
	spritePos.y = aSprite.GetPosition().y;
	spritePos -= myPosition;
	if (spritePos.x < boundMax && spritePos.x > boundMin && spritePos.y < boundMax && spritePos.y > boundMin)
	{
		spritePos.x *= myZoomFactor;
		spritePos.y *= myZoomFactor;
		aSprite.SetSizeRelativeToImage({1 * myZoomFactor, 1 * myZoomFactor});
		aSprite.SetPosition({ spritePos.x, spritePos.y });
	}
}

void Camera::BatchRenderSprite(RenderCommand& aRenderCommand)
{
	const float boundMax = 1.20f / myZoomFactor;
	const float boundMin = -0.20f / myZoomFactor;
	CommonUtilities::Vector2f spritePos;
	spritePos.x = aRenderCommand.GetPosition().x - (myPosition.x * myZoomFactor);
	spritePos.y = aRenderCommand.GetPosition().y - (myPosition.y * myZoomFactor);
	if (spritePos.x < boundMax && spritePos.x > boundMin && spritePos.y < boundMax && spritePos.y > boundMin)
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
	const float boundMax = 1.20f / myZoomFactor;
	const float boundMin = -0.20f / myZoomFactor;
	CommonUtilities::Vector2f spritePos;
	spritePos.x = aRenderCommand.GetPosition().x - (myPosition.x * myZoomFactor);
	spritePos.y = aRenderCommand.GetPosition().y - (myPosition.y * myZoomFactor);
	if (aRenderCommand.myShouldBeCulled)
	{
		if (spritePos.x < boundMax && spritePos.x > boundMin && spritePos.y < boundMax && spritePos.y > boundMin)
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
