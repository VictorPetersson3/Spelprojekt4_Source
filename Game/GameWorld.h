#pragma once
#include "CommonUtilities/Timer.h"

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
	Camera* myCamera;
	Tga2D::CSprite* myTga2dLogoSprite;
	testObjectsWithPositions* testObjects[100];
};