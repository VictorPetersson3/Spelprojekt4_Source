#pragma once
#include <tga2d/math/vector2.h>

class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update(const float aDt);
	void Render();

private:
	void LoadJsonData();
	void Movement();
	
	float myAcceleration = {};
	Tga2D::Vector2f myCurrentVelocity = {};	

};