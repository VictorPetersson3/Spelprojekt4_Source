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
	CommonUtilities::Vector2f position = { 0.0f, 1.0f };
	mySpeed = { &(aPlayer.GetCurrentVelocity().x), &(aPlayer.GetCurrentVelocity().y) };

	Layer layer1;
	Layer layer2;
	Layer layer3;

	switch (aWorld)
	{
	case EWorldLevel::eWorld1:
		layer1.mySprite = RenderCommand("Sprites/Backgrounds/world_01/back_world_01.dds" , 1, position, false);
		layer2.mySprite = RenderCommand("Sprites/Backgrounds/world_01/mid_world_01.dds"  , 1, position, false);
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
			layer.mySprite.SetPivot({ 0, 1.0f });
			layer.mySprite.SetSizeRelativeToImage({ 2.0f / 3.0f, 2.0f / 3.0f });
		}
	}
	//printf("render size x : %d, y : %d\n", RESOLUTION.x, RESOLUTION.y);
	//printf("size of image : %f\n", layer1.mySprite.GetSize().x);
	//printf("size of image size/res : %f\n", (float)layer1.mySprite.GetImageSize().x / (float)RESOLUTION.x);
	//printf("size of 1024 : %f\n", 1024.0f / RESOLUTION.x);
	//printf("size of size * 2 / 3 : %f\n", (float)layer1.mySprite.GetSize().x * 2.0f / 3.0f);
	//printf("size of 1024 / res * 2 / 3 : %f\n", 1024.0f / RESOLUTION.x * 2.0f / 3.0f);
	for (int i = 0; i < 4; i++)
	{
		for (auto& layer : mySets[i])
		{
			layer.myPosition = { position.x + i * 1024.0f / 1280.0f * 2.0f / 3.0f - 0.5f / RESOLUTION.x, position.y };
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
			mySets[i][j].myPosition.y += *mySpeed.y * mySpeedFactor[0] * DELTA_TIME;

			if (mySets[i][j].myPosition.x > 1 && *mySpeed.x > 0)
			{
				mySets[i][j].myPosition.x -= 4 * + 1024.0f / 1280.0f * 2.0f / 3.0f - 0.5f / RESOLUTION.x;
			}
			else if (mySets[i][j].myPosition.x + 1024.0f / 1280.0f * 2.0f / 3.0f - 0.5f / RESOLUTION.x < 0 && *mySpeed.x < 0)
			{
				mySets[i][j].myPosition.x += 4 * + 1024.0f / 1280.0f * 2.0f / 3.0f - 0.5f / RESOLUTION.x;
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
