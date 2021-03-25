#include "stdafx.h"
#include "Background.h"

#include "AnimationClip.h"
#include "Camera.h"
#include "Player.h"
#include "Timer.h"

#define DELTA_TIME Timer::GetInstance().GetDeltaTime()

Background::Background(EWorld_but_like_just_a_placeholder_for_the_real_tag aWorld)
{
	myWorld = aWorld;
}

void Background::Init(Player& aPlayer, CommonUtilities::Vector2f aPosition)
{
	mySpeed = { &(aPlayer.GetCurrentVelocity().x), &(aPlayer.GetCurrentVelocity().x) };

	Layer layer1;
	Layer layer2;
	Layer layer3;

	switch (myWorld)
	{
	case EWorld_but_like_just_a_placeholder_for_the_real_tag::Forest:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_01/background_03.dds", 1, aPosition);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_01/background_02.dds", 1, aPosition);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_01/background_01.dds", 1, aPosition);
		break;
	case EWorld_but_like_just_a_placeholder_for_the_real_tag::Level2:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_02/background_03.dds", 1, aPosition);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_02/background_02.dds", 1, aPosition);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_02/background_01.dds", 1, aPosition);
		break;
	case EWorld_but_like_just_a_placeholder_for_the_real_tag::Factory_Kanske:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_03/background_03.dds", 1, aPosition);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_03/background_02.dds", 1, aPosition);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_03/background_01.dds", 1, aPosition);
		break;
	case EWorld_but_like_just_a_placeholder_for_the_real_tag::MinnsInteVadDennaSkulleVaraHeller:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_04/background_03.dds", 1, aPosition);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_04/background_02.dds", 1, aPosition);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_04/background_01.dds", 1, aPosition);
		break;
	}

	mySets[0][0] = layer1;
	mySets[0][1] = layer2;
	mySets[0][2] = layer3;

	mySets[1] = mySets[0];
	mySets[2] = mySets[0];

	for (auto& set : mySets)
	{
		for (auto& layer : set)
		{
			layer.mySprite.SetPivot({ 0, 0.5f });
		}
	}

	for (auto& layer : mySets[0])
	{
		layer.myPosition = aPosition;
	}
	for (auto& layer : mySets[1])
	{
		layer.myPosition = { aPosition.x + layer.mySprite.GetSize().x, aPosition.y };
	}
	for (auto& layer : mySets[2])
	{
		layer.myPosition = { aPosition.x + layer.mySprite.GetSize().x * 2, aPosition.y };
	}
}

void Background::Update(Camera& aCamera)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (*mySpeed.x > 0)
			{
				int bajs = 2;
			}
			mySets[i][j].myPosition.x += *mySpeed.x * mySpeedFactor[j] * DELTA_TIME;
			//mySets[i][j].myPosition.y += *mySpeed.y * mySpeedFactor[0] * DELTA_TIME;

			/*if (mySets[i][j].myPosition.x > 1 && *mySpeed.x > 0)
			{
				mySets[i][j].myPosition.x -= 3 * mySets[i][j].mySprite.GetSize().x;
			}
			else if (mySets[i][j].myPosition.x + mySets[i][j].mySprite.GetSize().x < 0 && *mySpeed.x < 0)
			{
				mySets[i][j].myPosition.x -= 3 * mySets[i][j].mySprite.GetSize().x;
			}*/

			mySets[i][j].Update(aCamera);
		}
	}
}

void Layer::Update(Camera& aCamera)
{
	mySprite.Update(myPosition);
	aCamera.RenderSprite(mySprite);
}
