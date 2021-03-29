#pragma once
#include <vector>
#include "State.h"
#include "Enums.h"
#include <memory>
#include "CommonUtilities/GrowingArray.hpp"

class Entity;
class Player;
class Background;
class Camera;
class LevelData;
class Collider;
class PauseMenu;
class EndOfLevelScreen;
struct TerrainTile;

namespace Tga2D
{
	class CSpriteBatch;
}

class Level : public State
{
public:
	Level();
	~Level();

	void OnPushed() override;
	virtual void Render() override;
	virtual void Update() override;
	void Load(std::shared_ptr<LevelData> aData);
	void Load(int aIndex);
	void Restart();
	void LoadNextLevel();

	virtual void Init(const EStateType& aState) override;

private:

	

	std::shared_ptr<PauseMenu> myPauseMenu;
	std::shared_ptr<EndOfLevelScreen> myEndOfLevelScreen;
	std::shared_ptr<Camera> myCamera;
	std::shared_ptr<Player> myPlayer;
	std::unique_ptr<Background> myBackground;

	std::shared_ptr<LevelData> currentLevelData;

	std::vector<std::shared_ptr<TerrainTile>> myTerrain;
	std::vector<std::shared_ptr<Entity>> myEntities;

	std::shared_ptr<Collider> myLevelEndCollider;

	CommonUtilities::GrowingArray<std::shared_ptr<Tga2D::CSpriteBatch>> mySpriteBatches;

	int currentLevelIndex = 0;
	int amountOfLevels = 0;
};

