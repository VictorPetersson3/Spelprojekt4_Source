#include "stdafx.h"
#include "Collider.h"
#include "Camera.h"
#include "Timer.h"
#include "Door.h"
#include "Key.h"

#include <iostream>
#define DELTA_TIME Timer::GetInstance().GetDeltaTime()

void Door::Init(std::shared_ptr<Key> aKey)
{
	myCollider = std::make_shared<Collider>(myPosition, 0.05f, 0.05f);
	myRenderCommand = std::make_shared<RenderCommand>("sprites/");



}

void Door::Update()
{
	if (myKey->GetKeyState())
	{
		Unlock();
	}
}

void Door::Render(std::shared_ptr<Camera> aCamera)
{
	aCamera->RenderSprite(*myRenderCommand.get());
}

void Door::Unlock()
{
	std::cout << "Delete myself \n";

	delete this;
	// Tar bort detta objektet
}
