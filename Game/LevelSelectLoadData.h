#pragma once
#include "CommonUtilities/GrowingArray.hpp"
#include "LinkString.h"
#include "JsonParser.h"
#include "Enums.h"

class LevelSelect_SpecificLevelData;
class LevelSelectLoadData
{
public:
	friend class LevelSelect;
	LevelSelectLoadData()
	{
		myLevelSelectLoadData.Init(20);
	}
	void CreateLevelSelectButtonData();
private:
	void FillData(rapidjson::Value& aJsonValue, int& aDataIterator, EWorldLevel aWorld);
	CommonUtilities::GrowingArray<std::shared_ptr<LevelSelect_SpecificLevelData>> myLevelSelectLoadData;
	LinkString World1Song;
	LinkString World2Song;
	LinkString World3Song;
	LinkString World4Song;
};

