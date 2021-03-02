#pragma once
#include <map>
#include <Windows.h>
#include "Vector2.hpp"

// Spelprojektbaserat - Spel 3 Grupp 5
#include <string>
#include <vector>

namespace CommonUtilities
{
	enum class eMouseInput
	{
		eLPressed,
		eRPressed,
		eMiddlePressed,
		eLUp,
		eRUp,
		eMiddleUp,
		eLDown,
		eRDown,
		eMiddleDown,
		eEnd
	};

	class InputManager
	{
	public:

		InputManager();

		bool IsKeyPressed(const int aKeyCode) const;
		bool IsKeyUp(const int aKeyCode) const;
		bool IsKeyDown(const int aKeyCode) const;

		//Mouse Events

		Vector2f GetMousePosition() const;
		Vector2f GetMouseDelta() const;

		bool GetMouseLDown() const;
		bool GetMouseRDown() const;
		bool GetMouseLReleased() const;
		bool GetMouseRReleased() const;
		bool GetMouseLPressed() const;
		bool GetMouseRPressed() const;
		bool GetMouseMDown() const;
		bool GetMouseMReleased() const;
		bool GetMouseMPressed() const;
		float GetScroll() const;
		void SetMousePos(const Vector2f aPosition);

		//Other functions
		void Update();
		void LockMouseToWindow(bool aLockMouse);
		bool UpdateMouseInputEvents(HWND hwndMain, UINT message, WPARAM wParam, LPARAM lParam);

		void BindCustomKeys(int aCustomKey, std::initializer_list<int> aKeyCodes);
		bool IsCustomKeyDown(int aCustomKey) const;
		bool IsCustomKeyPressed(int aCustomKey) const;

	private:
		Vector2f myMousePosition;
		Vector2f myDelta;
		float myScroll;
		std::map<int, bool> myCurrentKeyMap;
		std::map<int, bool> myPreviousKeyMap;
		std::map<eMouseInput, bool> myMouseMap;

		std::map<int, std::vector<int>> myCustomKeyBindings;
	};
}


