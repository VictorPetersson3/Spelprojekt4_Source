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
	MainMenu(XController* aControllerPointer) : MenuObject(aControllerPointer) {}
	~MainMenu() = default;
	void Init(const EStateType& aState) final;
	void Update() final;
	void Render() final;
	void OnPushed() override;
private:
	void TestMe(int aVal);
	void OptionsButtonPress();
	void ExitButtonPress();
	void PlayButtonPress();
	std::unique_ptr<UIImage> myBackground;
	std::unique_ptr<UIImage> myPanningBackground;
	std::unique_ptr<UIImage> myLogo;
	std::unique_ptr<UIImage> myLogoHeart1;
	std::unique_ptr<UIImage> myLogoHeart2;
	std::unique_ptr<UIImage> myLogoHeart3;
	std::unique_ptr<UIImage> myLogoHeart4;
	std::shared_ptr<Tga2D::CCustomShader> myPanningShader;
	std::shared_ptr<Tga2D::CCustomShader> myBeatingShader;
	int myCurrentHoveredButton = 0;
};

