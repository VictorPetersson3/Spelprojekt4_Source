#pragma once
#include <memory>
#include <CommonUtilities/Vector2.hpp>
class Player;
class RenderCommand;
class Camera;

class Key
{
public:
	Key() = default;
	~Key() = default;

	void Init(std::shared_ptr<Player> aPlayer, const int aId);
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

private:

	bool myIsPickedUp = false;
	const int myId = 0;          // Detta är ett id som level design ska kunna använda för att ha flera olika nycklar i samma level
	const float myRange = 0.025f;


	CommonUtilities::Vector2f myPosition;
	std::shared_ptr<Player> myPlayer;
	std::shared_ptr<RenderCommand> myRenderCommand;

};

