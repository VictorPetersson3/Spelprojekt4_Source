#pragma once
#include "LinkString.h"
#include "CommonUtilities/Vector2.hpp"
#include "Enums.h"

struct LevelSelect_SpecificLevelData
{
	LinkString myLevelPath;
	LinkString myTileSheetPath;
	LinkString myPropsTileSheetPath;
	LinkString myBackgroundTilesTileSheetPath;
	LinkString myMapTile;
	EWorldLevel myWorld;
	CommonUtilities::Vector2f myPosition;
	CommonUtilities::Vector2f myCameraPosition;
	bool myHasCutscene = false;
	bool myIsUnlocked = false;
	bool myMoveCameraX = false;
	bool myMoveCameraY = false;
	int myCutsceneConversation = INFINITY;
	int myLevelNumber;
	float myCameraAcceleration;
	float myCameraMinBorderX;
	float myCameraMinBorderY;
	float myCameraMaxBorderX;
	float myCameraMaxBorderY;
	
	
};

