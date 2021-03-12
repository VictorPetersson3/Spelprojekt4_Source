#pragma once
#include "CommonUtilities/Timer.h"
#include <memory>
#include "MainMenu.h"


class Player;

namespace Tga2D
{
	class CSprite;
	class FBXModel;
	class CAudio;
}
class testObjectsWithPositions;
class Collider;
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
	std::shared_ptr<Camera> myCamera;
	Tga2D::CSprite* myTga2dLogoSprite;

	Collider* myCollider;
};