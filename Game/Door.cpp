#include "stdafx.h"
#include "Door.h"
#include "Key.h"
#include "Timer.h"

#define DELTA_TIME Timer::GetInstance().GetDeltaTime()

void Door::Init()
{
	
}

void Door::Update()
{
	if (myKey->GetKeyState())
	{
		Unlock();
	}
}

void Door::Render()
{

}

void Door::Unlock()
{
	delete this;
	// Tar bort detta objektet
}
