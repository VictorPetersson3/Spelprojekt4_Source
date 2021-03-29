#pragma once
#include "LinkString.h"
#include "CommonUtilities/Vector2.hpp"
#include "Enums.h"

struct LevelSelect_SpecificLevelData
{
	LinkString myLevelPath;
	LinkString myTileSheetPath;
	LinkString myPropsTileSheetPath;
	LinkString myMapTile;
	EWorldLevel myWorld;
	CommonUtilities::Vector2f myPosition;
	bool myHasCutscene = false;
	int myCutsceneConversation = INFINITY;
	int myLevelNumber;
};

