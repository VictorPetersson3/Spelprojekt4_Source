#include "stdafx.h"
#include "Level.h"
#include "LevelLoader.h"
#include "Player.h"
#include "Camera.h"
#include "Camera.h"
#include "Timer.h"
#include "InputManager.h"
#include "RenderCommand.h"
#include "Collider.h"
#include "tga2d/sprite/sprite_batch.h"
#include "CollisionManager.h"
#include "Background.h"
#include "Shooter.h"

#include "LevelData.h"
#include "Saw.h"
#include "TerrainTile.h"

#include "UIImage.h"

#include "AudioManager.h"
#include "StateManager.h"
#include "PauseMenu.h"
#include "EndOfLevelScreen.h"

Level::Level()
{
	myPlayer = std::make_unique<Player>();
	mySpriteBatches.Init(10);

	myPauseMenu = std::make_shared<PauseMenu>();
	myPauseMenu->Init(EStateType::ePauseMenu);
	myEndOfLevelScreen = std::make_shared<EndOfLevelScreen>(this);
	myEndOfLevelScreen->Init(EStateType::eEndOfLevelScreen);
	
	myBackground = std::make_unique<Background>(/*EWorld_but_like_just_a_placeholder_for_the_real_tag::Forest*/);
}

Level::~Level()
{

}

void Level::OnPushed()
{
	AudioManager::GetInstance().StopAllMusic();
}

void Level::Render()
{
	for (int i = 0; i < mySpriteBatches.Size(); i++)
	{
		mySpriteBatches[i]->Render();
	}

	for (auto entity : myEntities)
	{
		entity->Render(myCamera);
	}
}

void Level::Update()
{
	//Pause Menu
	if (InputManagerS::GetInstance().GetKeyDown(DIK_ESCAPE))
	{
		StateManager::AddStateOnStack(myPauseMenu);
	}
	//Player
	myCamera->Update({ 0,0 });	
	float deltaTime = Timer::GetInstance().GetDeltaTime();

	for (auto t : myTerrain)
	{
		myCamera->BatchRenderSprite(t.get()->myRenderCommand);
	}

	for (auto entity : myEntities)
	{
		entity.get()->Update(deltaTime);
	}

	if (InputManagerS::GetInstance().GetKeyDown(DIK_F5))
	{
		Restart();
	}

	if (InputManagerS::GetInstance().GetKeyDown(DIK_F4))
	{
		Load(1);
	}
	
	if (myPlayer.get() != nullptr)
	{
		myPlayer.get()->Update(*(myCamera.get()));
		myPlayer.get()->GetCollider().get()->Draw();
		if (myPlayer->IsDead())
		{
			Restart();
			return;
		}
	}
	
	if (myLevelEndCollider != nullptr)
	{
		myLevelEndCollider.get()->Draw();
	}
	
	if (myLevelEndCollider != nullptr && myPlayer.get() != nullptr)
	{
		if (CollisionManager::GetInstance().CheckCollision(myPlayer->GetCollider().get(), myLevelEndCollider.get()))
		{
			StateManager::AddStateOnStack(myEndOfLevelScreen);
			std::cout << "Level ended" << std::endl;
		}
	}	
	// Background
	if (myBackground != nullptr)
	{
		myBackground->Update(*(myCamera.get()));
	}
}

void Level::Load(std::shared_ptr<LevelData> aData)
{
	for (int i = 0; i < mySpriteBatches.Size(); i++)
	{
		mySpriteBatches[i]->ClearAll();
	}


	if (myPlayer.get()->GetCollider().get() != nullptr)
	{
		myPlayer.get()->GetCollider().get()->RemoveFromManager();
	}

	for (auto t : myTerrain)
	{
		t.get()->myCollider.get()->RemoveFromManager();
	}
	
	if (myLevelEndCollider != nullptr)
	{
		myLevelEndCollider.get()->RemoveFromManager();
	}

	myLevelEndCollider = aData.get()->GetLevelEnd();

	myTerrain.clear();

	myTerrain = aData->GetTiles();
	myEntities = aData->GetEntities();

	for (int i = 0; i < aData->GetSpriteBatches().Size(); i++)
	{
		mySpriteBatches.Add(aData->GetSpriteBatches()[i]);

	}

	for (auto t : myTerrain)
	{
		t->myCollider->AddToManager();
	}

	//for (auto shooter : myShooters)
	//{
	//	shooter.get()->SetManager(myBulletManager);
	//}

	myPlayer.get()->Init({ aData.get()->GetPlayerStart().x, aData.get()->GetPlayerStart().y });

	if (myLevelEndCollider != nullptr)
	{
		myLevelEndCollider->AddToManager();
	}

	if (myPlayer->GetCollider().get() != nullptr)
	{
		myPlayer->GetCollider()->AddToManager();
	}
}

void Level::Load(int aIndex)
{
	LevelLoader levelLoader;

	amountOfLevels = levelLoader.GetAmountOfLevels();

	Load(levelLoader.LoadLevel(aIndex));
	currentLevelIndex = aIndex;
}

void Level::Restart()
{
	LevelLoader levelLoader;
	Load(levelLoader.LoadLevel(currentLevelIndex));
}

void Level::LoadNextLevel()
{
	if (currentLevelIndex == amountOfLevels)
	{
		StateManager::GetInstance().RemoveDownToState(EStateType::eMainMenu);
	}
	else
	{
		Load(currentLevelIndex++);
	}
}

void Level::Init(const EStateType& aState)
{
	std::cout << "level inited\n";
	//Creating a camera and then a renderer for the camera
	myCamera = std::make_shared<Camera>();

	currentLevelIndex = 0;

	myBackground->Init(*(myPlayer.get()));
}
