#pragma once
#include "MenuObject.h"
#include "UIImage.h"


class MainMenu : public MenuObject
{
public:
	MainMenu() = default;
	~MainMenu() = default;
	void Init();
	void Update();
	void TestMe(int aVal);
	void Test2();
private:
	std::unique_ptr<UIImage> myBackground;
	int myCurrentHoveredButton = 0;
};

