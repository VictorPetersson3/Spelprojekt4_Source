#pragma once
#include "MenuObject.h"
#include "UIImage.h"
#include "LinkString.h"

namespace Tga2D
{
	class CCustomShader;
}

class MainMenu : public MenuObject
{
public:
	MainMenu() = default;
	~MainMenu() = default;
	void Init(const EStateType& aState) final;
	void Update() final;
	void Render() final;
	void OnPushed() override;
private:
	void TestMe(int aVal);
	void OptionsButtonPress();
	void ExitButtonPress();
	std::unique_ptr<UIImage> myBackground;
	std::unique_ptr<UIImage> myPanningBackground;
	std::shared_ptr<Tga2D::CCustomShader> myPanningShader;
	int myCurrentHoveredButton = 0;
};

