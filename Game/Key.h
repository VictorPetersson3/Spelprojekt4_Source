#pragma once
#include <memory>
#include <CommonUtilities/Vector2.hpp>
#include "Entity.h"

class Player;
class RenderCommand;
class Camera;

class Key : public Entity
{
public:
	Key();
	~Key() = default;

	void Init(std::shared_ptr<Player> aPlayer);
	void Update(float aDeltaTime) override;
	void Render(std::shared_ptr<Camera> aCamera) override;
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
	inline void SetIndex(const int aIndex)
	{
		myIndex = aIndex;
	}
private:

	bool myIsPickedUp = false;
    int myIndex = 0;          // Detta är ett id som level design ska kunna använda för att ha flera olika nycklar i samma level
	const float myRange = 0.025f;


	CommonUtilities::Vector2f myPosition;
	std::shared_ptr<Player> myPlayer;
	std::shared_ptr<RenderCommand> myRenderCommand;

};

