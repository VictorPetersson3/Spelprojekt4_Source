#pragma once
#include "Entity.h"
#include <memory>
#include <CommonUtilities/Vector2.hpp>
class Player;
class RenderCommand;
class Camera;

class Key : public Entity
{
public:
	Key() = default;
	~Key() = default;

	void Init(std::shared_ptr<Player> aPlayer);
	void Update();
	void Render(std::shared_ptr<Camera> aCamera);
	bool CheckState();
	inline bool GetKeyState() const 
	{
		return myIsPickedUp;
	}
	inline void SetPosition(CommonUtilities::Vector2f aPosition)
	{
		myPosition = aPosition;
	}
	inline int GetIndex() const 
	{
		return myIndex;
	}
private:

	bool myIsPickedUp = false;
    int myIndex = 0;          // Detta �r ett id som level design ska kunna anv�nda f�r att ha flera olika nycklar i samma level
	const float myRange = 0.025f;


	CommonUtilities::Vector2f myPosition;
	std::shared_ptr<Player> myPlayer;
	std::shared_ptr<RenderCommand> myRenderCommand;

};

