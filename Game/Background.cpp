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

void Background::Init(Player& aPlayer, EWorldLevel aWorld)
{
	CommonUtilities::Vector2f position = { 0.0f, aPlayer.GetPosition().y + 0.51f };
	mySpeed = { &(aPlayer.GetCurrentVelocity().x), &(aPlayer.GetCurrentVelocity().y) };

	Layer layer1;
	Layer layer2;
	Layer layer3;

	switch (aWorld)
	{
	case EWorldLevel::eWorld1:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_01/back_world_01.dds", 1, position, false);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_01/mid_world_01.dds", 1, position, false);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_01/front_world_01.dds", 1, position, false);
		break;
	case EWorldLevel::eWorld2:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_02/back_world_02.dds", 1, position, false);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_02/mid_world_02.dds", 1, position, false);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_02/front_world_02.dds", 1, position, false);
		break;
	case EWorldLevel::eWorld3:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_03/back_world_03.dds", 1, position, false);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_03/mid_world_03.dds", 1, position, false);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_03/front_world_03.dds", 1, position, false);
		break;
	case EWorldLevel::eWorld4:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_04/back_world_04.dds", 1, position, false);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_04/mid_world_04.dds", 1, position, false);
		layer3.mySprite = RenderCommand("Sprites/Backgrounds/world_04/front_world_04.dds", 1, position, false);
		break;
	}

	layer1.mySprite.SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);
	layer2.mySprite.SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);
	layer3.mySprite.SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);
	layer1.mySprite.SetBlendState(EBlendState::EBlendState_Alphablend);
	layer2.mySprite.SetBlendState(EBlendState::EBlendState_Alphablend);
	layer3.mySprite.SetBlendState(EBlendState::EBlendState_Alphablend);

	mySets[0][0] = layer1;
	mySets[0][1] = layer2;
	mySets[0][2] = layer3;

	mySets[1] = mySets[0];
	mySets[2] = mySets[0];
	mySets[3] = mySets[0];
	mySets[4] = mySets[0];

	for (auto& set : mySets)
	{
		for (auto& layer : set)
		{
			layer.mySprite.SetPivot({ 0, 1.0f });
			layer.mySprite.SetSizeRelativeToImage({ 1, 1 });
		}
	}
	//printf("render size x : %d, y : %d\n", 1280.0f, RESOLUTION.y);
	//printf("size of image : %f\n", layer1.mySprite.GetSize().x);
	//printf("size of image size/res : %f\n", (float)layer1.mySprite.GetImageSize().x / (float)1280.0f);
	//printf("size of 1024 : %f\n", 1024.0f / 1280.0f);
	//printf("size of size * 2 / 3 : %f\n", (float)layer1.mySprite.GetSize().x * 2.0f / 3.0f);
	//printf("size of 1024 / res * 2 / 3 : %f\n", 1024.0f / 1280.0f * 2.0f / 3.0f);
	for (int i = 0; i < 5; i++)
	{
		for (auto& layer : mySets[i])
		{
			layer.myPosition = { position.x + i * 0.8f, position.y };
		}
	}

	Update();
}

void Background::Update()
{
	float bigDelta = 0.8f;
	float smallDelta = *mySpeed.x * DELTA_TIME;

	int smolIndex = 5;
	float smolness = 10;

	mySets[0][0].myPosition.x -= mySpeedFactor[0] * smallDelta;
	mySets[0][1].myPosition.x -= mySpeedFactor[1] * smallDelta;
	mySets[0][2].myPosition.x -= mySpeedFactor[2] * smallDelta;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mySets[i][j].myPosition.x = mySets[0][j].myPosition.x + bigDelta * i;
			//mySets[i][j].myPosition.y -= *mySpeed.y * mySpeedFactor[j] / 8 * DELTA_TIME;

			if (mySets[i][j].myPosition.x - bigDelta > 1)
			{
				if (i < 4)
				{
					mySets[i][j].myPosition.x = mySets[i + 1][j].myPosition.x - bigDelta;
				}
				else
				{
					mySets[i][j].myPosition.x = mySets[0][j].myPosition.x - bigDelta;
				}
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
	mySets[4][0].Render(aCamera);
	mySets[0][1].Render(aCamera);
	mySets[1][1].Render(aCamera);
	mySets[2][1].Render(aCamera);
	mySets[3][1].Render(aCamera);
	mySets[4][1].Render(aCamera);
	mySets[0][2].Render(aCamera);
	mySets[1][2].Render(aCamera);
	mySets[2][2].Render(aCamera);
	mySets[3][2].Render(aCamera);
	mySets[4][2].Render(aCamera);
}

void Layer::Update()
{
	mySprite.Update(myPosition);
}

void Layer::Render(Camera& aCamera)
{
	aCamera.RenderSprite(mySprite);
}
