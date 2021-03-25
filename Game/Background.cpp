#include "stdafx.h"
#include "Background.h"

#include "AnimationClip.h"
#include "Camera.h"
#include "Player.h"
#include "Timer.h"

#define DELTA_TIME Timer::GetInstance().GetDeltaTime()
#define RESOLUTION Tga2D::CEngine::GetInstance()->GetRenderSize()

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
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_01/prarlllaa.dds", 1, aPosition, false);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_01/prarlllaa(1).dds", 1, aPosition, false);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_01/prarlllaa(2).dds", 1, aPosition, false);
		break;
	case EWorld_but_like_just_a_placeholder_for_the_real_tag::Level2:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_02/background_03.dds", 1, aPosition, false);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_02/background_02.dds", 1, aPosition, false);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_02/background_01.dds", 1, aPosition, false);
		break;
	case EWorld_but_like_just_a_placeholder_for_the_real_tag::Factory_Kanske:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_03/background_03.dds", 1, aPosition, false);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_03/background_02.dds", 1, aPosition, false);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_03/background_01.dds", 1, aPosition, false);
		break;
	case EWorld_but_like_just_a_placeholder_for_the_real_tag::MinnsInteVadDennaSkulleVaraHeller:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_04/background_03.dds", 1, aPosition, false);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_04/background_02.dds", 1, aPosition, false);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_04/background_01.dds", 1, aPosition, false);
		break;
	}

	mySets[0][0] = layer1;
	mySets[0][1] = layer2;
	mySets[0][2] = layer3;

	mySets[1] = mySets[0];
	mySets[2] = mySets[0];
	mySets[3] = mySets[0];

	for (auto& set : mySets)
	{
		for (auto& layer : set)
		{
			layer.mySprite.SetPivot({ 0, 0.5f });
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (auto& layer : mySets[i])
		{
			layer.myPosition = { aPosition.x + i * 512.0f / RESOLUTION.x , aPosition.y };
		}
	}
}

void Background::Update()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mySets[i][j].myPosition.x += *mySpeed.x * mySpeedFactor[j] * DELTA_TIME;
			//mySets[i][j].myPosition.y += *mySpeed.y * mySpeedFactor[0] * DELTA_TIME;

			if (mySets[i][j].myPosition.x > 1 && *mySpeed.x > 0)
			{
				mySets[i][j].myPosition.x -= 4 * + 512.0f / RESOLUTION.x;
			}
			else if (mySets[i][j].myPosition.x + 512.0f / RESOLUTION.x < 0 && *mySpeed.x < 0)
			{
				mySets[i][j].myPosition.x += 4 * + 512.0f / RESOLUTION.x;
			}
			mySets[i][j].Update();
		}
	}
}

void Background::Render(Camera& aCamera)
{
	mySets[0][0].Render(aCamera);
	mySets[1][0].Render(aCamera);
	mySets[2][0].Render(aCamera);
	mySets[3][0].Render(aCamera);
	mySets[0][1].Render(aCamera);
	mySets[1][1].Render(aCamera);
	mySets[2][1].Render(aCamera);
	mySets[3][1].Render(aCamera);
	mySets[0][2].Render(aCamera);
	mySets[1][2].Render(aCamera);
	mySets[2][2].Render(aCamera);
	mySets[3][2].Render(aCamera);
}

void Layer::Update()
{
	mySprite.Update(myPosition);
}

void Layer::Render(Camera& aCamera)
{
	aCamera.RenderSprite(mySprite);
}
