#include "stdafx.h"
#include "Key.h"
#include "Camera.h"
#include "RenderCommand.h"
#include "Player.h"
void Key::Init(std::shared_ptr<Player> aPlayer) 
{
	myPlayer = aPlayer;
	myRenderCommand = std::make_shared<RenderCommand>("sprites/");

}

void Key::Update()
{
	if (CheckState() && !myIsPickedUp)
	{
		myIsPickedUp = true;
	}
}

void Key::Render(std::shared_ptr<Camera> aCamera)
{
	aCamera->RenderSprite(*myRenderCommand.get());
}

bool Key::CheckState()
{
	const float dist = CommonUtilities::Vector2f::Distance(myPosition, myPlayer->GetPosition());
	return dist <= myRange;
}
