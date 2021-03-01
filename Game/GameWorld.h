#pragma once
#include "CommonUtilities/InputManager.h"
#include "CommonUtilities/Timer.h"


namespace Tga2D
{
	class CSprite;
	class FBXModel;
	class CAudio;
}

class CGameWorld
{
public:
	CGameWorld(CommonUtilities::InputManager* aInputManager, CommonUtilities::Timer* aTimer);
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render();
private:
	Tga2D::CSprite* myTga2dLogoSprite;
	CommonUtilities::InputManager* myInputManager;
	CommonUtilities::Timer* myGameTimer;

};