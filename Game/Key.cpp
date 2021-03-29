#include "stdafx.h"
#include "Key.h"
#include "Camera.h"
#include "RenderCommand.h"
#include "Player.h"
#include "InputManager.h"

void Key::Init(std::shared_ptr<Player> aPlayer, const int aId) 
{
	const_cast<int&>(myId) = aId;
	myPlayer = aPlayer;
	myRenderCommand = std::make_shared<RenderCommand>("sprites/tga_logo.dds", 1, true);
	myPosition = { 0.5f,0.5f };
}

void Key::Update() 
{
	if (InputManagerS::GetInstance().GetKeyDown(DIK_0))
	{
		myIsPickedUp = true;		
	}

	myRenderCommand->SetSpritePosition(myPosition);
	/*if (CheckState() && !myIsPickedUp)
	{
		myIsPickedUp = true;
	}*/

}

void Key::Render(std::shared_ptr<Camera> aCamera)
{
	aCamera->RenderSprite(*myRenderCommand);
}

bool Key::CheckState()
{
	const float dist = CommonUtilities::Vector2f::Distance(myPosition, myPlayer->GetPosition());
	return dist <= myRange;
}