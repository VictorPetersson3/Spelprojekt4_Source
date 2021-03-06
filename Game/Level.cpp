#include "stdafx.h"
#include "Level.h"
#include "LevelLoader.h"
#include "Player.h"
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
#include "CameraBehavoir.h"
#include "LevelData.h"
#include "Saw.h"
#include "TerrainTile.h"
#include "Boss.h"
#include "Emitter.h"

#include "UIImage.h"

#include "AudioManager.h"
#include "StateManager.h"
#include "PauseMenu.h"
#include "EndOfLevelScreen.h"
#include "LevelSelect_SpecificLevelData.h"

#include "XController.h"

Level::Level(XController* aControllerPointer) : myController(aControllerPointer)
{
	myPlayer = std::make_shared<Player>();
	mySpriteBatches.Init(10);

	myPauseMenu = std::make_shared<PauseMenu>(aControllerPointer);
	myPauseMenu->Init(EStateType::ePauseMenu);
	myEndOfLevelScreen = std::make_shared<EndOfLevelScreen>(this, aControllerPointer);
	myEndOfLevelScreen->Init(EStateType::eEndOfLevelScreen);

	myBackground = std::make_unique<Background>();
}

Level::~Level()
{

}

void Level::OnPushed()
{
	AudioManager::GetInstance().StopAllMusic();
	AudioManager::GetInstance().PlayMusic(mylevelJsonData->mySong.GetString(), true, 0.5f);
	if (myIsLastLevel)
	{
		AudioManager::GetInstance().StopAllMusic();
		AudioManager::GetInstance().PlayMusic("Audio/music/Boss_Song.mp3", true, 0.5f);
	}
}

void Level::Render()
{
	myCamera->Update();
	myBackground->Render(*myCamera);
	for (auto t : myTerrain)
	{
		myCamera->BatchRenderSprite(t.get()->myRenderCommand);
	}
	for (int i = 0; i < mySpriteBatches.Size(); i++)
	{
		mySpriteBatches[i]->Render();
	}

	for (auto entity : myEntities)
	{
		entity->Render(myCamera);
	}

	if (myBoss != nullptr)
	{
		myBoss->Render(*myCamera);
	}
	myPlayer->Render(*myCamera);
}




void Level::Update()
{
	myCameraController->Update(Timer::GetInstance().GetDeltaTime());
	const float deltaTime = Timer::GetInstance().GetDeltaTime();
	if (myBoss != nullptr)
	{
		myBoss->Update(deltaTime);
	}
	if (myPlayerHasDied == true)
	{
		myPlayer->SetShouldUpdatePhysics(false);

		myPlayerPhysicsUpdateCountdownTimer += deltaTime;
		if (myPlayerPhysicsUpdateCountdownTimer >= myPlayerPhysicsUpdateCountdown)
		{
			myPlayerHasDied = false;
			myPlayer->SetShouldUpdatePhysics(true);
			myPlayerPhysicsUpdateCountdownTimer = 0.f;
		}
		
	}
	//Pause Menu
	if (InputManagerS::GetInstance().GetKeyUp(DIK_ESCAPE) || myController->IsButtonPressed(XINPUT_GAMEPAD_START))
	{
		StateManager::AddStateOnStack(myPauseMenu);
	}
	
	//Player
	for (auto entity : myEntities)
	{
		entity.get()->Update(deltaTime);
	}

		
	if (myPlayer != nullptr)
	{
		if (deltaTime < 0.0166666666666667f) myPlayer->Update(*myCamera);
		//myPlayer->GetCollider()->Draw();
		if (myPlayer->IsDead() && myPlayerHasDied == false)
		{
			myPlayerHasDied = true;
			Restart();
			return;
		}
	}

	// Background
	if (myBackground != nullptr)
	{
		myBackground->Update(*myCamera);
	}

	// Remove before handing in
	/////////////////////

	if (myLevelEndCollider != nullptr && myPlayer.get() != nullptr)
	{
		if (CollisionManager::GetInstance().CheckCollision(myPlayer->GetCollider().get(), myLevelEndCollider.get()))
		{
			if (mylevelJsonData->myHasEndCutscene)
			{
				StateManager::AddAndPlayCutscene(mylevelJsonData->myEndCutsceneConversation, true);
			}
			else
			{
				StateManager::AddStateOnStack(myEndOfLevelScreen);
			}
		}
	}

	if (myAmbientParticles != nullptr) myAmbientParticles->Update({ myCamera->GetPosition().x + 0.5f, mylevelJsonData->myCameraMinBorderY - 0.3f }, *myCamera);
}

void Level::Load(std::shared_ptr<LevelData> aData, LevelSelect_SpecificLevelData* someLevelData)
{
	myBoss.reset();

	for (int i = 0; i < mySpriteBatches.Size(); i++)
	{
		mySpriteBatches[i]->ClearAll();
	}

	mySpriteBatches.RemoveAll();

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
	CollisionManager::GetInstance().Clear();

	myLevelEndCollider = aData.get()->GetLevelEnd();

	myTerrain.clear();

	myTerrain = aData->GetTiles();
	myEntities = aData->GetEntities();

	mySpriteBatches.Add(myAmbientParticles->GetBatch());

	for (int i = 0; i < aData->GetSpriteBatches().Size(); i++)
	{
		mySpriteBatches.Add(aData->GetSpriteBatches()[i]);
	}

	for (auto& t : myTerrain)
	{
		t->myCollider->AddToManager();
	}
	for (auto& e : myEntities)
	{
		for (std::shared_ptr<Collider> ec : e->GetAllColliders())
		{
			ec->AddToManager();
		}
	}

	if (myLevelEndCollider != nullptr)
	{
		myLevelEndCollider->AddToManager();
	}


	myPlayer.get()->Init({ aData.get()->GetPlayerStart().x, aData.get()->GetPlayerStart().y }, StateManager::GetInstance().GetSelectedCharacter(), mylevelJsonData->myWorld);


	if (someLevelData->myHasBoss)
	{
		myBoss = std::make_shared<Boss>();
		myBoss->Init(myPlayer);
	}

	//myBoss->Init(myPlayer);
	//myPlayer->SetShouldUpdatePhysics(false);
	myBackground->Init(*myCamera, mylevelJsonData->myWorld, mylevelJsonData->myWorldLevelNumber);

}

void Level::Load(LevelSelect_SpecificLevelData* someLevelData, const bool aReloadedLevel, const bool aLastLevel)
{
	LevelLoader levelLoader;
	mylevelJsonData = someLevelData;
	myEndOfLevelScreen->SetCurrentLevel(mylevelJsonData->myLevelSelectNumber);
	myIsLastLevel = aLastLevel;
	//L�gg in att den skall spela en cutscene h�r och att den laddar in den

	myAmbientParticles = std::make_shared<Emitter>(mylevelJsonData->myWorld);
	myAmbientParticles->Init({myCamera->GetPosition().x, mylevelJsonData->myCameraMinBorderY - 0.3f }, ParticleType::Ambient, mylevelJsonData->myWorld);

	Load(levelLoader.LoadLevel(mylevelJsonData), mylevelJsonData);


	myCameraController->SetAcceleration(someLevelData->myCameraAcceleration);
	myCameraController->SetMaxBoarderX(someLevelData->myCameraMaxBorderX);
	myCameraController->SetMinBoarderX(someLevelData->myCameraMinBorderX);
	myCameraController->SetMinBoarderY(someLevelData->myCameraMinBorderY);
	myCameraController->SetMaxBoarderY(someLevelData->myCameraMaxBorderY);
	myCameraController->SetPosition(someLevelData->myCameraPosition);
	myCameraController->SetMoveX(someLevelData->myMoveCameraX);
	myCameraController->SetMoveY(someLevelData->myMoveCameraY);
	myCameraController->Update(Timer::GetInstance().GetDeltaTime());

	if (mylevelJsonData->myHasCutscene && !aReloadedLevel)
	{
		StateManager::AddAndPlayCutscene(mylevelJsonData->myCutsceneConversation);
		OnPushed();
	}
}

void Level::Restart()
{
	LevelLoader levelLoader;
	Load(mylevelJsonData, true, myIsLastLevel);
	myCameraController->ResetCamera();
}

void Level::LoadNextLevel()
{
	bool amILastLevel = false;
	StateManager::GetInstance().AddNextLevelOnStack(mylevelJsonData->myLevelSelectNumber);
	return;
}

void Level::AddEndOfLevelOnStack()
{
	StateManager::AddStateOnStack(myEndOfLevelScreen);
}

void Level::Init(const EStateType& aState)
{
	myCamera = std::make_shared<Camera>();
	myCameraController = std::make_shared<CameraBehavoir>();
	myCameraController->Init(myCamera, myPlayer);
	

}
