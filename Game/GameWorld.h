#pragma once
#include "CommonUtilities/Timer.h"
#include <memory>

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
	std::unique_ptr<Camera> myCamera;
	Tga2D::CSprite* myTga2dLogoSprite;
};