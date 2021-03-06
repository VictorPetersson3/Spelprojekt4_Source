#pragma once
#include <vector>
#include "State.h"
#include "Enums.h"
#include <memory>
#include "CommonUtilities/GrowingArray.hpp"
class XController;
class Boss;
class Entity;
class Emitter;
class Player;
class Background;
class Camera;
class LevelData;
class Collider;
class PauseMenu;
class EndOfLevelScreen;
class CameraBehavoir;
struct LevelSelect_SpecificLevelData;
struct TerrainTile;

namespace Tga2D
{
	class CSpriteBatch;
}

class Level : public State
{
public:
	Level(XController* aControllerPointer);
	~Level();

	void OnPushed() override;
	virtual void Render() override;
	virtual void Update() override;
	void Load(std::shared_ptr<LevelData> aData, LevelSelect_SpecificLevelData* someLevelData);
	void Load(LevelSelect_SpecificLevelData* someLevelData, const bool aReloadedLevel, const bool aLastLevel);
	void Restart();
	void LoadNextLevel();
	void AddEndOfLevelOnStack();

	virtual void Init(const EStateType& aState) override;

private:

	LevelSelect_SpecificLevelData* mylevelJsonData;

	std::shared_ptr<Boss> myBoss = {};
	std::shared_ptr<Camera> myCamera = {};
	std::shared_ptr<Player> myPlayer = {};
	std::shared_ptr<PauseMenu> myPauseMenu = {};
	std::unique_ptr<Background> myBackground = {};
	std::shared_ptr<CameraBehavoir> myCameraController = {};
	std::shared_ptr<EndOfLevelScreen> myEndOfLevelScreen = {};


	std::shared_ptr<LevelData> currentLevelData;

	std::vector<std::shared_ptr<TerrainTile>> myTerrain;
	std::vector<std::shared_ptr<Entity>> myEntities;

	std::shared_ptr<Collider> myLevelEndCollider;

	CommonUtilities::GrowingArray<std::shared_ptr<Tga2D::CSpriteBatch>> mySpriteBatches;

	int currentLevelIndex = 0;
	int amountOfLevels = 0;

	float myPlayerPhysicsUpdateCountdownTimer = 0.f;
	float myPlayerPhysicsUpdateCountdown = 0.2f;

	bool myPlayerHasDied = false;
	bool myIsLastLevel = false;

	std::shared_ptr<Emitter> myAmbientParticles;
	XController* myController;
};

