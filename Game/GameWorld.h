#pragma once
#include "CommonUtilities/Timer.h"
#include <memory>
#include <vector>

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
class Door;
class Key;

class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render();
private:
	std::shared_ptr<Player> myPlayer;
	std::shared_ptr<XController> myController = {};
	std::shared_ptr<Camera> myCamera;
	


};