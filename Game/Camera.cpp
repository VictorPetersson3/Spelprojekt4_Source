#include "stdafx.h"
#include "Camera.h"
#include "Timer.h"
#include "InputManager.h"
#include "tga2d/sprite/sprite.h"
#include "RenderCommand.h"
#include "Sprite_Renderer.h"

Camera::Camera()
{
	myPosition.Zero;
	mySpriteRenderRef = nullptr;
	myMovementSpeed = 0.15f;
}

void Camera::Init(const CommonUtilities::Vector2f& aPos)
{
	myPosition = aPos;
	mySpriteRenderRef = nullptr;
}

void Camera::Init(const CommonUtilities::Vector2f& aPos, Sprite_Renderer* aSpriteRenderer)
{
	myPosition = aPos;
	mySpriteRenderRef = aSpriteRenderer;
}

//Here the logic for following the player will be or whatever we will follow or the rules we have
void Camera::Update(const CommonUtilities::Vector2f aPositionToFollow)
{
	if (InputManager::GetInstance().IsKeyDown('I'))
	{
		myPosition.y -= myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}
	if (InputManager::GetInstance().IsKeyDown('L'))
	{
		myPosition.x += myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}
	if (InputManager::GetInstance().IsKeyDown('J'))
	{
		myPosition.x -= myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}
	if (InputManager::GetInstance().IsKeyDown('K'))
	{
		myPosition.y += myMovementSpeed * Timer::GetInstance().GetDeltaTime();
	}
	//printf("CameraPos x: %f y: %f\n", myPosition.x, myPosition.y);
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
//Inte constat RenderCommandet då jag behöver arbeta på en kopia så jag kan ändra spriten
void Camera::BatchRenderSprite(const RenderCommand& aRenderCommand)
{
	CommonUtilities::Vector2f spritePos;
	spritePos.x = aRenderCommand.GetPosition().x;
	spritePos.y = aRenderCommand.GetPosition().y;
	spritePos.x = aRenderCommand.GetPosition().x - myPosition.x;
	spritePos.y = aRenderCommand.GetPosition().y - myPosition.y;
	if (spritePos.x < 1.0f && spritePos.x > 0.0f && spritePos.y < 1.0f && spritePos.y > 0.0f)
	{
		RenderCommand commandToBatch = aRenderCommand;
		Tga2D::CSprite aSpriteCopy = *aRenderCommand.mySprite.get();
		aSpriteCopy.SetPosition({ spritePos.x, spritePos.y });
		commandToBatch.ReplaceSpritePointerContent(aSpriteCopy);
		mySpriteRenderRef->AddRenderCommandToRenderer(commandToBatch);
	}
}
