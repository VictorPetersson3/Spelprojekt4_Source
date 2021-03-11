#pragma once
#include "TerrainTile.h"
#include <vector>
#include "State.h"
#include <memory>
#include "Saw.h"

class Level : public State
{
public:
	Level();
	~Level();


	void Render() override;
	void Update() override;

private:

	std::vector<std::shared_ptr<TerrainTile>> myTerrain;
	std::vector<std::shared_ptr<Saw>> mySaws;

};

