#include "stdafx.h"
#include "Background.h"

#include "AnimationClip.h"
#include "RenderCommand.h"
#include "Player.h"

void Background::Init(std::shared_ptr<Player> aPlayer, EWorld_but_like_just_a_placeholder_for_the_real_tag aWorld)
{
	mySpeed = aPlayer->GetCurrentVelocityPtr();

	switch (aWorld)
	{
	case EWorld_but_like_just_a_placeholder_for_the_real_tag::Forest:
		InitWorld1();
		break;
	case EWorld_but_like_just_a_placeholder_for_the_real_tag::Level2:
		InitWorld2();
		break;
	case EWorld_but_like_just_a_placeholder_for_the_real_tag::Factory_Kanske:
		InitWorld3();
		break;
	case EWorld_but_like_just_a_placeholder_for_the_real_tag::MinnsInteVadDennaSkulleVaraHeller:
		InitWorld4();
		break;
	}
}

void Background::Update()
{
	for (int i = 0; i < 4; i++)
	{
		myLayers[i]->myPosition += *mySpeed * mySpeedFactor[i];
		myLayers[i]->Update();
	}
}

void Background::InitWorld1()
{
	std::shared_ptr<AnimatedLayer> animLayer;
	animLayer->myAnimation = std::make_shared<AnimationClip>(("Sprites/Backgrounds/World1/animated_layer.dds"), 0, (int)EAnimatedBackgroundLayers::Fog);
	animLayer->myAnimation->Init({ 2, 1 }, { 2, 1 });
	animLayer->myAnimation->PlayAnimLoop();

	std::shared_ptr<StaticLayer> statLayer1;
	std::shared_ptr<StaticLayer> statLayer2;
	std::shared_ptr<StaticLayer> statLayer3;

	statLayer1->mySprite = std::make_shared<RenderCommand>("Sprites/Backgrounds/World1/background_layer1.dds");
	statLayer2->mySprite = std::make_shared<RenderCommand>("Sprites/Backgrounds/World1/background_layer2.dds");
	statLayer3->mySprite = std::make_shared<RenderCommand>("Sprites/Backgrounds/World1/background_layer3.dds");


}

void Background::InitWorld2()
{
}

void Background::InitWorld3()
{
}

void Background::InitWorld4()
{
}
