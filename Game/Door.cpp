#include "stdafx.h"
#include "Collider.h"
#include "Camera.h"
#include "Timer.h"
#include "Door.h"
#include "Key.h"
#include "RenderCommand.h"
#include <iostream>
#define DELTA_TIME Timer::GetInstance().GetDeltaTime()

void Door::Init(std::shared_ptr<Key> aKey)
{
	myKey = aKey;

	myCollider = std::make_shared<Collider>(myPosition, 0.05f, 0.05f);
	myRenderCommand = std::make_shared<RenderCommand>("sprites/tga_logo.dds", 1, true);
	myRenderCommand->SetSizeRelativeToImage({ 0.2f,0.2f });

}

void Door::Update(float)
{
	//myRenderCommand->SetSpritePosition(myPosition);
	if (!myIsDestoryed)
	{
		myRenderCommand->Update(myPosition);
		myCollider->UpdateCollider(myPosition);
		if (myKey->GetKeyState())
		{
			Unlock();
		}
	}
}

void Door::Render(std::shared_ptr<Camera> aCamera)
{
	if (!myIsDestoryed)
	{
		aCamera->RenderSprite(*myRenderCommand);
	}
}

void Door::Unlock()
{
	myIsDestoryed = true;
	myCollider->RemoveFromManager();
	// Tar bort detta objektet
}
