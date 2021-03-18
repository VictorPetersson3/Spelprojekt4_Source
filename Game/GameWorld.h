#pragma once
#include "CommonUtilities/Timer.h"
#include <memory>


class Player;
class XController;

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
	std::unique_ptr<Player> myPlayer;
	std::shared_ptr<XController> myController = {};
	bool t = false;
	int sm = 0;
	std::shared_ptr<Camera> myCamera;
	
};