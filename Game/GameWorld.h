#pragma once
#include "CommonUtilities/Timer.h"
#include <memory>
#include "MainMenu.h"

namespace Tga2D
{
	class CSprite;
	class FBXModel;
	class CAudio;
}
class testObjectsWithPositions;
class Camera;
class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render();
private:
	MainMenu mainMenu;
	std::unique_ptr<Camera> myCamera;
	Tga2D::CSprite* myTga2dLogoSprite;
};