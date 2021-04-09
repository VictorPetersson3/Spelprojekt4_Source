#include "stdafx.h"
#include "Background.h"

#include "AnimationClip.h"
#include "Camera.h"
#include "JsonParser.h"
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
	JsonParser parser;
	//auto cameraDoc = parser.GetDocument("Json/Camera.json");
	auto worldDoc = parser.GetDocument("Json/Levels.json");

	if (true/*!cameraDoc["..."]["IsStatic"].GetBool()*/) 
		mySpeed = { &(aPlayer.GetCurrentVelocity().x), &(aPlayer.GetCurrentVelocity().y) };
	
	CommonUtilities::Vector2f position = { 0.0f, aPlayer.GetPosition().y + 0.51f/*cameraDoc["..."]["MaxY"].GetFloat()*/ };

	std::string path = worldDoc["Worlds"][(int)aWorld]["backgroundFolderPath"].GetString();

	Layer layer1 = Layer(RenderCommand((path + "back.dds").c_str(), 1, position, false));
	Layer layer2 = Layer(RenderCommand((path + "mid.dds").c_str(), 1, position, false));
	Layer layer3 = Layer(RenderCommand((path + "front.dds").c_str(), 1, position, false));

	mySets[0][0] = layer1;
	mySets[0][1] = layer2;
	mySets[0][2] = layer3;

	mySets[1] = mySets[0];
	mySets[2] = mySets[0];
	mySets[3] = mySets[0];
	mySets[4] = mySets[0];

	for (int i = 0; i < mySets.size(); i++)
	{
		for (auto& layer : mySets[i])
		{
			layer.mySprite.SetPivot({ 0, 1.0f });
			layer.mySprite.SetSizeRelativeToImage({ 1, 1 });
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
			if (myShouldPanY) mySets[i][j].myPosition.y -= *mySpeed.y * mySpeedFactor[j] / 8 * DELTA_TIME;

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

Layer::Layer(const RenderCommand aRenderCommand)
{
	mySprite = aRenderCommand;
	mySprite.SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Wrap);
	//mySprite.SetBlendState(EBlendState::EBlendState_Alphablend);
}

void Layer::Update()
{
	mySprite.Update(myPosition);
}

void Layer::Render(Camera& aCamera)
{
	aCamera.RenderSprite(mySprite);
}
