#pragma once
#include "CommonUtilities/Timer.h"
class Player;

namespace Tga2D
{
	class CSprite;
	class FBXModel;
	class CAudio;
}

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

	Tga2D::CSprite* myTga2dLogoSprite;
};