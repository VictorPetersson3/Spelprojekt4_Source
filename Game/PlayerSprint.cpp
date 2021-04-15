#include "stdafx.h"
#include "PlayerSprint.h"
#include "Timer.h"
#include "Camera.h"
#include <tga2d/sprite/sprite.h>
#include "AnimationClip.h"
#include "RenderCommand.h"
#include <random>
#include <cmath>

#define DELTA_TIME Timer::GetInstance().GetDeltaTime()

PlayerSprint::PlayerSprint()
{
}

PlayerSprint::~PlayerSprint()
{
	delete mySprite;
	mySprite = nullptr;
}

void PlayerSprint::Init(EWorldLevel aWorld)
{
	myWorld = aWorld;

	// Emission Values
	/// Spawn time
	myContents.myMinTimeBetweenParticleSpawns = 0.02f;
	myContents.myMaxTimeBetweenParticleSpawns = 0.06f;
	/// Emission time
	/*myEmitTime = 0.0f;*/

	// Local Ranges 
	/// Scale
	myMinStartScale = 1.0f;
	myMaxStartScale = 1.0f;

	//myStartScale = 1.0f;
	myEndScale = 1.0f;

	/// Start Speed
	myMinStartSpeed = 0.01f;
	myMaxStartSpeed = 0.02f;

	/// Angle
	myMinRotation = -2.0f;
	myMaxRotation = 2.0f;

	/// Lifetime
	myMinLifeTime = 0.2f;
	myMaxLifeTime = 0.5f;

	/// Color
	switch (myWorld)
	{
	case EWorldLevel::eWorld1:
		myStartColor = { 0.8f, 0.91015625f, 1.0f, 0.9f };
		myEndColor = { 0.171875f, 0.25390625f, 0.4453125f, 0.7f };
		break;
	case EWorldLevel::eWorld2:
		myStartColor = { 0.80078125f, 0.68359375f, 0.6484375f, 0.9f };
		myEndColor = { 0.234375f, 0.1875f, 0.1875f, 0.7f };
		break;
	case EWorldLevel::eWorld3:
		myStartColor = { 0.87109375f, 0.3203125f, 0.6171875f, 0.9f };
		myEndColor = { 0.578125f, 0.234375f, 0.6484375f, 0.5f };
		break;
	case EWorldLevel::eWorld4:
		myStartColor = { 0.87109375f, 0.3203125f, 0.6171875f, 0.9f };
		myEndColor = { 0.578125f, 0.234375f, 0.6484375f, 0.7f };
		break;
	}

	/// Acceleration
	myMinAcceleration = { 0.99f, 0.99f };
	myMaxAcceleration = { 0.9999f, 0.9999f };
	myGravity = 0.01f;

	// Setting values
	/// Blend State
	myBlendState = EBlendState::EBlendState_Alphablend;

	/// Sprite
	//mySprite = new Tga2D::CSprite("Sprites/Particles/big_player_run_particle_w.dds");
	switch (rand() % 4)
	{
	case 0:
		mySprite = new Tga2D::CSprite("Sprites/Particles/tiny_player_run_particle_w.dds");
		break;
	case 1:
		mySprite = new Tga2D::CSprite("Sprites/Particles/small_player_run_particle_w.dds");
		break;
	case 2:
		mySprite = new Tga2D::CSprite("Sprites/Particles/medium_player_run_particle_w.dds");
		break;
	case 3:
		mySprite = new Tga2D::CSprite("Sprites/Particles/big_player_run_particle_w.dds");
		break;
	}
	mySprite->SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetBlendState(myBlendState);

	Reset();
}


void PlayerSprint::Reset()
{
	std::random_device rd;
	std::mt19937 randomInt(rd());

	// Setting values
	/// Color
	mySprite->SetColor({ myStartColor });

	/// Scale
	std::uniform_real_distribution<> scaleDist(myMinStartScale, myMaxStartScale);
	myStartScale = scaleDist(randomInt);

	/// Angle
	std::uniform_real_distribution<> rotationDist(myMinRotation, myMaxRotation);
	myRotation = rotationDist(randomInt);

	/// Sprite
	mySprite->SetSizeRelativeToImage({ myStartScale, myStartScale });

	/// Speed
	std::uniform_real_distribution<> speedDist(myMinStartSpeed, myMaxStartSpeed);
	mySpeed = speedDist(randomInt);
	std::uniform_real_distribution<> periodDist(0.5f, 3.0f);
	myPeriod = periodDist(randomInt);

	/// Velocity
	std::uniform_real_distribution<> velocityDist(-100, 100);
	myVelocity.x = velocityDist(randomInt) / 100.0f;
	myVelocity.y = velocityDist(randomInt) / 200.0f;
	if (!myVelocity.x) myVelocity.x += 0.001f;
	if (!myVelocity.y) myVelocity.y += 0.001f;
	myVelocity.x *= 9.0f / 16.0f;
	myVelocity *= mySpeed;
	/// Lifetime
	std::uniform_real_distribution<> LTDist(myMinLifeTime, myMaxLifeTime);
	myLifeTime = LTDist(randomInt);

	/// Acceleration
	std::uniform_real_distribution<> accelerationDist(myMinAcceleration.x, myMaxAcceleration.x);
	myAcceleration.x = accelerationDist(randomInt);
	std::uniform_real_distribution<> acceleration(myMinAcceleration.y, myMaxAcceleration.y);
	myAcceleration.y = acceleration(randomInt);

	/// Time
	myTime = 0;
}

void PlayerSprint::Update(const CommonUtilities::Vector2f& aCamera, const float& aPercentage)
{
	// Gör vad fan du vill här, det är ingenting som är "permanent".
	myTime += DELTA_TIME;

	myVelocity.x = powf(myAcceleration.x, DELTA_TIME) * myVelocity.x/* + sinf(myPeriod * myTime) * 0.05f * DELTA_TIME*/;
	myVelocity.y = powf(myAcceleration.y, DELTA_TIME) * myVelocity.y + myGravity * DELTA_TIME;

	myAngle += myRotation * DELTA_TIME;

	myPosition.x += myVelocity.x * DELTA_TIME;
	myPosition.y += myVelocity.y * DELTA_TIME;

	mySprite->SetPosition({ myPosition.x - aCamera.x, myPosition.y - aCamera.y });
	mySprite->SetRotation(myAngle);

	float alpha = myStartColor.myA + (myTime / myLifeTime) * (myEndColor.myA - myStartColor.myA);
	mySprite->SetColor({ myStartColor.myR, myStartColor.myG, myStartColor.myB, alpha });
}

void PlayerSprint::SetPosition(CommonUtilities::Vector2f aPosition)
{
	myPosition = aPosition;
}

Tga2D::CSprite* PlayerSprint::GetSprite()
{
	return mySprite;
}