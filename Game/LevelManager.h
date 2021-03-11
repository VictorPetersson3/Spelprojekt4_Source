#pragma once
#include <vector>
#include <memory>

class Level;

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void Init();
	void Update();

private:
	std::vector<std::shared_ptr<Level>> myLevels;

	int myCurrentLevel = 0;
};

