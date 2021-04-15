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
	LinkString mySong;
	EWorldLevel myWorld;
	CommonUtilities::Vector2f myPosition;
	CommonUtilities::Vector2f myCameraPosition;
	bool myHasCutscene = false;
	bool myHasEndCutscene = false;
	bool myIsUnlocked = false;
	bool myMoveCameraX = false;
	bool myMoveCameraY = false;
	bool myHasBoss = true;
	int myCutsceneConversation = INFINITY;
	int myEndCutsceneConversation = INFINITY;
	int myLevelSelectNumber;
	int myWorldLevelNumber;
	float myCameraAcceleration;
	float myCameraMinBorderX;
	float myCameraMinBorderY;
	float myCameraMaxBorderX;
	float myCameraMaxBorderY;
	
	
};

