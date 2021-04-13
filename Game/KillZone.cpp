#include "stdafx.h"
#include "KillZone.h"
#include "Collider.h"
#include "CollisionManager.h"

KillZone::KillZone(float aWidth, float aHeight, CommonUtilities::Vector2f aPosition)
{

	aWidth /= 1280.f;
	aHeight /= 720.f;

	aPosition.x -= 16.f;
	aPosition.y -= 16.f;

	aPosition.x /= 1280.f;
	aPosition.y /= 720.f;


	myCollider = std::make_shared<Collider>(aPosition,aWidth, aHeight);

	myCollider->SetTag(EColliderTag::KillZone);
}

KillZone::~KillZone()
{
	myCollider->RemoveFromManager();
}

void KillZone::Update(float aDeltaTime)
{
	
}
void KillZone::Render(const std::shared_ptr<Camera> aCamera)
{
}

std::vector<std::shared_ptr<Collider>> KillZone::GetAllColliders()
{
	std::vector<std::shared_ptr<Collider>> returnVector;
	returnVector.push_back(myCollider);
	return returnVector;
}
