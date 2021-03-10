#pragma once
#include "MenuObject.h"
#include "UIImage.h"

class MainMenu : public MenuObject
{
public:
	MainMenu() = default;
	~MainMenu() = default;
	void Init(const EStateType& aState) final;
	void Update() final;
	void Render() final;
private:
	void TestMe(int aVal);
	void OptionsButtonPress();
	void ExitButtonPress();
	std::unique_ptr<UIImage> myBackground;
	int myCurrentHoveredButton = 0;
};

