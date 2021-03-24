#include "stdafx.h"
#include "Key.h"
#include "Player.h"
void Key::Init(std::shared_ptr<Player> aPlayer) 
{
	myPlayer = aPlayer;

}

void Key::Update()
{
	if (CheckState() && !myIsPickedUp)
	{
		myIsPickedUp = true;
	}
}

void Key::Render()
{

}

bool Key::CheckState()
{
	const float dist = CommonUtilities::Vector2f::Distance(myPosition, myPlayer->GetPosition());
	return dist <= myRange;
}
