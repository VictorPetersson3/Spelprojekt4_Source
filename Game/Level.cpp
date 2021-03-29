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
#include "Door.h"
#include "Key.h"

#include "LevelData.h"
#include "Saw.h"
#include "TerrainTile.h"

#include "UIImage.h"

#include "AudioManager.h"
#include "StateManager.h"
#include "PauseMenu.h"
#include "EndOfLevelScreen.h"

#include "LevelSelect_SpecificLevelData.h"

Level::Level()
{
	myPlayer = std::make_shared<Player>();
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
	myBackground->Render(*myCamera);

	for (int i = 0; i < mySpriteBatches.Size(); i++)
	{
		mySpriteBatches[i]->Render();
	}

	for (auto entity : myEntities)
	{
		entity->Render(myCamera);
	}

	myPlayer->Render(*myCamera);
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
		entity->Render(myCamera);
	}

	if (InputManagerS::GetInstance().GetKeyDown(DIK_F5))
	{
		Restart();
	}
		
	if (myPlayer.get() != nullptr)
	{
		myPlayer.get()->Update();
		myPlayer.get()->GetCollider().get()->Draw();
		if (myPlayer->IsDead())
		{
			Restart();
			return;
		}
	}

	if (myLevelEndCollider != nullptr)
	{
		myLevelEndCollider->Draw();
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
	//if (myBackground != nullptr)
	{
		myBackground->Update();
	}
}

void Level::Load(std::shared_ptr<LevelData> aData, LevelSelect_SpecificLevelData* someLevelData)
{
	for (int i = 0; i < mySpriteBatches.Size(); i++)
	{
		mySpriteBatches[i]->ClearAll();
	}

	if (myPlayer->GetCollider().get() != nullptr)
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

	std::vector<std::shared_ptr<Key>> keyList = {};
	std::vector<Door*> doorList = {};
	for (int i = 0; i < myEntities.size(); i++)
	{
		if (Key* key = dynamic_cast<Key*>(myEntities[i].get()))
		{
			keyList.emplace_back(dynamic_cast<Key*>(myEntities[i].get()));
			key->Init(myPlayer);
		}
		if (Door* door = dynamic_cast<Door*>(myEntities[i].get()))
		{
			doorList.emplace_back(dynamic_cast<Door*>(myEntities[i].get()));
		}
	}
	for (int i = 0; i < doorList.size(); i++)
	{
		for (int j = 0; j < keyList.size(); j++)
		{
			if (doorList[i]->GetIndex() == keyList[j]->GetIndex())
			{
				doorList[i]->Init(keyList[j]);
			}
		}
	}
	keyList.clear();
	doorList.clear();


	for (int i = 0; i < aData->GetSpriteBatches().Size(); i++)
	{
		mySpriteBatches.Add(aData->GetSpriteBatches()[i]);

	}

	for (auto t : myTerrain)
	{
		t->myCollider->AddToManager();
	}

	myPlayer.get()->Init({ aData.get()->GetPlayerStart().x, aData.get()->GetPlayerStart().y });

	if (myLevelEndCollider != nullptr)
	{
		myLevelEndCollider->AddToManager();
	}

	//if (myPlayer->GetCollider().get() != nullptr)
	//{
	//	myPlayer->GetCollider()->AddToManager();
	//}
}

void Level::Load(LevelSelect_SpecificLevelData* someLevelData)
{
	LevelLoader levelLoader;
	mylevelButtondata = someLevelData;
	myEndOfLevelScreen->SetCurrentLevel(mylevelButtondata->myLevelNumber);
	//L�gg in att den skall spela en cutscene h�r och att den laddar in den

	Load(levelLoader.LoadLevel(mylevelButtondata), mylevelButtondata);
	myBackground->Init(*(myPlayer.get()), mylevelButtondata->myWorld);
}

void Level::Restart()
{
	LevelLoader levelLoader;
	Load(levelLoader.LoadLevel(mylevelButtondata), mylevelButtondata);
}

void Level::LoadNextLevel()
{
	bool amILastLevel = false;
	StateManager::GetInstance().AddNextLevelOnStack(mylevelButtondata->myLevelNumber);
	return;
}

void Level::Init(const EStateType& aState)
{
	std::cout << "level inited\n";
	//Creating a camera and then a renderer for the camera
	myCamera = std::make_shared<Camera>();
}
