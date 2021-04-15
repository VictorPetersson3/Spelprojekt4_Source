#include "stdafx.h"
#include "Boss.h"
#include "Player.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "Collider.h"
#include "JsonParser.h"
#include "AudioManager.h"
#include "AnimationClip.h"
#include <string>
#include <iostream>
#include <CommonUtilities/Random.h>
void Boss::Init(const std::shared_ptr<Player> aPlayer)
{

	myRenderCommand = std::make_shared<RenderCommand>("sprites/HästfanDDS.dds", 1, true);
	myRenderCommand->SetSizeRelativeToImage({ 3.f,3.f });
	myRenderCommand->SetPivot({ 0.5f,0.5f });
	myRenderCommand->SetSamplerState(ESamplerFilter_Point, ESamplerAddressMode_Clamp);

	myPlayerToAttack = aPlayer;
	myPosition = { 0.5f, 0.5f }; // start pos
	myPostionsToMoveTo.emplace_back(myPosition);

	myRenderCommand->SetSpritePosition(myPosition);

	myCollider = std::make_shared<Collider>(myPosition, 0.15f, 0.15f);
	myCollider->SetTag(EColliderTag::KillZone);
	LoadJson();
	LoadAnimations();

}

void Boss::Update(const float aDt)
{
	if (!myIsDead)
	{
		Move(aDt);
		myPosition += myDirection * aDt;
		myRenderCommand->SetSpritePosition(myPosition);
		myRenderCommand->Update(myPosition);
		myCollider->Update();
		myCollider->UpdateCollider(myPosition);

		if (myDirection.Length() < 0.1f)
		{
			ChangeAnimState(AnimationState::eIdleL);
		}
		for (int i = 0; i < myAnimations.size(); i++)
		{
			myAnimations[i]->UpdateAnimation(myPosition);
		}
		myDirection = CommonUtilities::Vector2f::Zero();
		
	}
}

void Boss::Render(Camera& aCamera)
{
	if (!myIsDead)
	{
		if (myPlayerToAttack->GetPosition().x < myPosition.x)
		{
			aCamera.RenderSprite(myAnimations[(int)myAnimationState]->GetRenderCommand());
		}
		else
		{
			aCamera.RenderSprite(myAnimations[(int)myAnimationState + 1]->GetRenderCommand());
		}
	}
}

void Boss::AddForce(const CommonUtilities::Vector2f aForce)
{
	myDirection += aForce;
}

void Boss::ChangeAnimState(const AnimationState aAnimationState)
{
	myAnimationState = aAnimationState;
}


void Boss::Move(const float aDt)
{
	PickNewPosition(aDt);
	const float dist = CommonUtilities::Vector2f::Distance(myPostionsToMoveTo[myPositionIndex], myPlayerToAttack->GetPosition());
	if (dist > 0.05f)
	{
		const float maxSpeed = mySpeed * 2;
		if (myPlayDash)
		{
			ChangeAnimState(AnimationState::eDashL);
			myPlayDash = false;
		}
		CommonUtilities::Vector2f direction = myPostionsToMoveTo[myPositionIndex] - myPosition;
		AddForce((direction.Clamp(-maxSpeed, maxSpeed) * mySpeed));
		return;
	}
}

void Boss::LoadAnimations()
{
	myAnimations.emplace_back(std::make_shared<AnimationClip>("Sprites/boss/boss_idle_L.dds", 2, 0));
	myAnimations.emplace_back(std::make_shared<AnimationClip>("Sprites/boss/boss_idle_R.dds", 2, 1));

	myAnimations.emplace_back(std::make_shared<AnimationClip>("Sprites/boss/boss_tell_L.dds", 2, 2));
	myAnimations.emplace_back(std::make_shared<AnimationClip>("Sprites/boss/boss_tell_R.dds", 2, 3));

	myAnimations.emplace_back(std::make_shared<AnimationClip>("Sprites/boss/boss_dash_L.dds", 2, 4));
	myAnimations.emplace_back(std::make_shared<AnimationClip>("Sprites/boss/boss_dash_R.dds", 2, 5));

	for (int i = 0; i < myAnimations.size(); ++i)
	{
		myAnimations[i]->GetRenderCommand().SetSamplerState(ESamplerFilter_Point, ESamplerAddressMode_Clamp);
		if (i > 3)
			myAnimations[i]->Init({ 4, 1 }, { 3, 1 });
		else
			myAnimations[i]->Init({ 4, 1 }, { 4, 1 });
		
		myAnimations[i]->PlayAnimLoop();
		myAnimations[i]->SetScaleRelativeToFrame({ 1.5f,1.5f });
	}
}

void Boss::LoadJson()
{
	JsonParser parser;
	auto doc = parser.GetDocument("Json/Boss.json");

	myMoveTimerMax = doc["MoveTimerMax"].GetFloat();
	myMoveTimerMin = doc["MoveTimerMin"].GetFloat();

	myPosition.x = doc["Position"]["X"].GetFloat();
	myPosition.x = doc["Position"]["Y"].GetFloat();


	mySpeed = doc["Speed"].GetFloat();

	for (int i = 0; i < doc["BossPositions"].Size(); i++)
	{
		AddDashPosition({ doc["BossPositions"][i]["X"].GetFloat() , doc["BossPositions"][i]["Y"].GetFloat() });
	}
}

int Boss::PickPosition()
{
	int index = 0;
	float dist = 0, closestDist = 0;
	for (int i = 0; i < myPostionsToMoveTo.size(); ++i)
	{
		dist = CommonUtilities::Vector2f::Distance(myPostionsToMoveTo[i], myPlayerToAttack->GetPosition());
		if (dist < closestDist || closestDist == 0)
		{
			closestDist = dist;
			index = i;
		}
	}
	return index;
}

void Boss::PickNewPosition(const float aDt)
{
	if (myMoveTimer >= myMoveTime)
	{
		const int rnd = rand() % 10000;
		if (rnd > 5000)
		{
			AudioManager::GetInstance().PlayEffect("Audio/Boss/swoosh.waw");
		}
		else
		{
			AudioManager::GetInstance().PlayEffect("Audio/Boss/swoosh.waw");
		}
		myPositionIndex = PickPosition();
		myPlayDash = true;
		myMoveTimer = 0;
		myMoveTime = CommonUtilities::GetRandomFloat(myMoveTimerMin, myMoveTimerMax);
		return;
	}
	
	myMoveTimer += aDt;
}
