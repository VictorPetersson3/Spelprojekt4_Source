#pragma once
#include <vector>
#include "State.h"
#include "Enums.h"
#include <memory>
#include "CommonUtilities/GrowingArray.hpp"


class Player;
class Camera;
class LevelData;
class Saw;
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
	std::unique_ptr<Camera> myCamera;
	std::unique_ptr<Player> myPlayer;

	std::shared_ptr<LevelData> currentLevelData;

	std::vector<std::shared_ptr<TerrainTile>> myTerrain;
	std::vector<std::shared_ptr<Saw>> mySaws;

	std::shared_ptr<Collider> myLevelEndCollider;

	CommonUtilities::GrowingArray<std::shared_ptr<Tga2D::CSpriteBatch>> mySpriteBatches;

	int currentLevelIndex = 0;
	int amountOfLevels = 0;
};

