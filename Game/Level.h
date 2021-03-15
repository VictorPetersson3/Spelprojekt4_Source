#pragma once
#include "TerrainTile.h"
#include <vector>
#include "State.h"
#include "Enums.h"
#include <memory>
#include "Saw.h"
#include "LevelData.h"

class Player;
class Camera;
class Sprite_Renderer;

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
	std::unique_ptr<Camera> myCamera;
	std::unique_ptr<Player> myPlayer;
	std::shared_ptr<Sprite_Renderer> mySpriteRenderer;
	std::vector<std::shared_ptr<TerrainTile>> myTerrain;
	std::vector<std::shared_ptr<Saw>> mySaws;

};

