#pragma once

#include "KeyCodes.h"

#include <map>
#include <string_view>
#include <vector>

namespace xengine {

	struct KeyData
	{
		KeyCode Key;
		KeyState State = KeyState::None;
		KeyState OldState = KeyState::None;
	};

	class Input
	{
	public:
		static void Update();

		static bool IsKeyPressed(KeyCode keycode);
		static bool IsKeyHeld(KeyCode keycode);

		static void UpdateKeyState(KeyCode key, KeyState newState);

	private:
		inline static std::map<KeyCode, KeyData> s_KeyData;
	};

}
