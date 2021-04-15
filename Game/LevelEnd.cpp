#include "stdafx.h"
#include "LevelEnd.h"
#include "RenderCommand.h"
#include "AnimationClip.h"
#include "Camera.h"

void LevelEnd::Init(const Vector2 aPosition, const Vector2 aSize, std::string aImagePath)
{
	myPosition = aPosition;
	myCollider = std::make_shared<Collider>(myPosition, aSize.x, aSize.y);
	myCollider->SetTag(EColliderTag::EndZone);

	aImagePath.erase(aImagePath.begin(), aImagePath.begin() + 6);

	myRenderCommand = std::make_shared<AnimationClip>(aImagePath.c_str(), 5, 0);
	myRenderCommand->UpdateAnimation(myPosition);
	//myRenderCommand->SetSpritePosition(myPosition);
}

void LevelEnd::Update(float aDeltaTime)
{
	myCollider->UpdateCollider(myPosition);
}

void LevelEnd::Render(std::shared_ptr<Camera> aCamera)
{
	//aCamera->BatchRenderSprite(*myRenderCommand);
	aCamera->RenderSprite(myRenderCommand->GetRenderCommand());
	myCollider->Draw();
}

std::vector<std::shared_ptr<Collider>> LevelEnd::GetAllColliders()
{
	std::vector<std::shared_ptr<Collider>> returnVector;
	returnVector.push_back(myCollider);
	return returnVector;
}
