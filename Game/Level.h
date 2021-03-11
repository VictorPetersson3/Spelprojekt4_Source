#pragma once
#include "TerrainTile.h"
#include <vector>
#include "State.h"
#include "Enums.h"
#include <memory>
#include "Saw.h"
#include "LevelData.h"

class Player;

class Level : public State
{
public:
	Level();
	~Level();


	virtual void Render() override;
	virtual void Update() override;
	void Load(std::shared_ptr<LevelData> aData);

	virtual void Init(const EStateType& aState) override;

private:

	std::unique_ptr<Player> myPlayer;

	std::vector<std::shared_ptr<TerrainTile>> myTerrain;
	std::vector<std::shared_ptr<Saw>> mySaws;

};

