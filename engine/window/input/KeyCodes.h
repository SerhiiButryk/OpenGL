#pragma once

#include <ostream>
#include <cstdint>

namespace xengine
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	enum class KeyState
	{
		None = -1,
		Pressed,
		Held,
		Released
	};

	enum class CursorMode
	{
		Normal = 0,
		Hidden = 1,
		Locked = 2
	};

	typedef enum class MouseButton : uint16_t
	{
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Left = Button0,
		Right = Button1,
		Middle = Button2
	} Button;


	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, MouseButton button)
	{
		os << static_cast<int32_t>(button);
		return os;
	}
}

// From glfw3.h
#define XE_KEY_SPACE           ::xengine::Key::Space
#define XE_KEY_APOSTROPHE      ::xengine::Key::Apostrophe    /* ' */
#define XE_KEY_COMMA           ::xengine::Key::Comma         /* , */
#define XE_KEY_MINUS           ::xengine::Key::Minus         /* - */
#define XE_KEY_PERIOD          ::xengine::Key::Period        /* . */
#define XE_KEY_SLASH           ::xengine::Key::Slash         /* / */
#define XE_KEY_0               ::xengine::Key::D0
#define XE_KEY_1               ::xengine::Key::D1
#define XE_KEY_2               ::xengine::Key::D2
#define XE_KEY_3               ::xengine::Key::D3
#define XE_KEY_4               ::xengine::Key::D4
#define XE_KEY_5               ::xengine::Key::D5
#define XE_KEY_6               ::xengine::Key::D6
#define XE_KEY_7               ::xengine::Key::D7
#define XE_KEY_8               ::xengine::Key::D8
#define XE_KEY_9               ::xengine::Key::D9
#define XE_KEY_SEMICOLON       ::xengine::Key::Semicolon     /* ; */
#define XE_KEY_EQUAL           ::xengine::Key::Equal         /* = */
#define XE_KEY_A               ::xengine::Key::A
#define XE_KEY_B               ::xengine::Key::B
#define XE_KEY_C               ::xengine::Key::C
#define XE_KEY_D               ::xengine::Key::D
#define XE_KEY_E               ::xengine::Key::E
#define XE_KEY_F               ::xengine::Key::F
#define XE_KEY_G               ::xengine::Key::G
#define XE_KEY_H               ::xengine::Key::H
#define XE_KEY_I               ::xengine::Key::I
#define XE_KEY_J               ::xengine::Key::J
#define XE_KEY_K               ::xengine::Key::K
#define XE_KEY_L               ::xengine::Key::L
#define XE_KEY_M               ::xengine::Key::M
#define XE_KEY_N               ::xengine::Key::N
#define XE_KEY_O               ::xengine::Key::O
#define XE_KEY_P               ::xengine::Key::P
#define XE_KEY_Q               ::xengine::Key::Q
#define XE_KEY_R               ::xengine::Key::R
#define XE_KEY_S               ::xengine::Key::S
#define XE_KEY_T               ::xengine::Key::T
#define XE_KEY_U               ::xengine::Key::U
#define XE_KEY_V               ::xengine::Key::V
#define XE_KEY_W               ::xengine::Key::W
#define XE_KEY_X               ::xengine::Key::X
#define XE_KEY_Y               ::xengine::Key::Y
#define XE_KEY_Z               ::xengine::Key::Z
#define XE_KEY_LEFT_BRACKET    ::xengine::Key::LeftBracket   /* [ */
#define XE_KEY_BACKSLASH       ::xengine::Key::Backslash     /* \ */
#define XE_KEY_RIGHT_BRACKET   ::xengine::Key::RightBracket  /* ] */
#define XE_KEY_GRAVE_ACCENT    ::xengine::Key::GraveAccent   /* ` */
#define XE_KEY_WORLD_1         ::xengine::Key::World1        /* non-US #1 */
#define XE_KEY_WORLD_2         ::xengine::Key::World2        /* non-US #2 */

/* Function keys */
#define XE_KEY_ESCAPE          ::xengine::Key::Escape
#define XE_KEY_ENTER           ::xengine::Key::Enter
#define XE_KEY_TAB             ::xengine::Key::Tab
#define XE_KEY_BACKSPACE       ::xengine::Key::Backspace
#define XE_KEY_INSERT          ::xengine::Key::Insert
#define XE_KEY_DELETE          ::xengine::Key::Delete
#define XE_KEY_RIGHT           ::xengine::Key::Right
#define XE_KEY_LEFT            ::xengine::Key::Left
#define XE_KEY_DOWN            ::xengine::Key::Down
#define XE_KEY_UP              ::xengine::Key::Up
#define XE_KEY_PAGE_UP         ::xengine::Key::PageUp
#define XE_KEY_PAGE_DOWN       ::xengine::Key::PageDown
#define XE_KEY_HOME            ::xengine::Key::Home
#define XE_KEY_END             ::xengine::Key::End
#define XE_KEY_CAPS_LOCK       ::xengine::Key::CapsLock
#define XE_KEY_SCROLL_LOCK     ::xengine::Key::ScrollLock
#define XE_KEY_NUM_LOCK        ::xengine::Key::NumLock
#define XE_KEY_PRINT_SCREEN    ::xengine::Key::PrintScreen
#define XE_KEY_PAUSE           ::xengine::Key::Pause
#define XE_KEY_F1              ::xengine::Key::F1
#define XE_KEY_F2              ::xengine::Key::F2
#define XE_KEY_F3              ::xengine::Key::F3
#define XE_KEY_F4              ::xengine::Key::F4
#define XE_KEY_F5              ::xengine::Key::F5
#define XE_KEY_F6              ::xengine::Key::F6
#define XE_KEY_F7              ::xengine::Key::F7
#define XE_KEY_F8              ::xengine::Key::F8
#define XE_KEY_F9              ::xengine::Key::F9
#define XE_KEY_F10             ::xengine::Key::F10
#define XE_KEY_F11             ::xengine::Key::F11
#define XE_KEY_F12             ::xengine::Key::F12
#define XE_KEY_F13             ::xengine::Key::F13
#define XE_KEY_F14             ::xengine::Key::F14
#define XE_KEY_F15             ::xengine::Key::F15
#define XE_KEY_F16             ::xengine::Key::F16
#define XE_KEY_F17             ::xengine::Key::F17
#define XE_KEY_F18             ::xengine::Key::F18
#define XE_KEY_F19             ::xengine::Key::F19
#define XE_KEY_F20             ::xengine::Key::F20
#define XE_KEY_F21             ::xengine::Key::F21
#define XE_KEY_F22             ::xengine::Key::F22
#define XE_KEY_F23             ::xengine::Key::F23
#define XE_KEY_F24             ::xengine::Key::F24
#define XE_KEY_F25             ::xengine::Key::F25

/* Keypad */
#define XE_KEY_KP_0            ::xengine::Key::KP0
#define XE_KEY_KP_1            ::xengine::Key::KP1
#define XE_KEY_KP_2            ::xengine::Key::KP2
#define XE_KEY_KP_3            ::xengine::Key::KP3
#define XE_KEY_KP_4            ::xengine::Key::KP4
#define XE_KEY_KP_5            ::xengine::Key::KP5
#define XE_KEY_KP_6            ::xengine::Key::KP6
#define XE_KEY_KP_7            ::xengine::Key::KP7
#define XE_KEY_KP_8            ::xengine::Key::KP8
#define XE_KEY_KP_9            ::xengine::Key::KP9
#define XE_KEY_KP_DECIMAL      ::xengine::Key::KPDecimal
#define XE_KEY_KP_DIVIDE       ::xengine::Key::KPDivide
#define XE_KEY_KP_MULTIPLY     ::xengine::Key::KPMultiply
#define XE_KEY_KP_SUBTRACT     ::xengine::Key::KPSubtract
#define XE_KEY_KP_ADD          ::xengine::Key::KPAdd
#define XE_KEY_KP_ENTER        ::xengine::Key::KPEnter
#define XE_KEY_KP_EQUAL        ::xengine::Key::KPEqual

#define XE_KEY_LEFT_SHIFT      ::xengine::Key::LeftShift
#define XE_KEY_LEFT_CONTROL    ::xengine::Key::LeftControl
#define XE_KEY_LEFT_ALT        ::xengine::Key::LeftAlt
#define XE_KEY_LEFT_SUPER      ::xengine::Key::LeftSuper
#define XE_KEY_RIGHT_SHIFT     ::xengine::Key::RightShift
#define XE_KEY_RIGHT_CONTROL   ::xengine::Key::RightControl
#define XE_KEY_RIGHT_ALT       ::xengine::Key::RightAlt
#define XE_KEY_RIGHT_SUPER     ::xengine::Key::RightSuper
#define XE_KEY_MENU            ::xengine::Key::Menu

// Mouse
#define XE_MOUSE_BUTTON_LEFT    ::xengine::Button::Left
#define XE_MOUSE_BUTTON_RIGHT   ::xengine::Button::Right
#define XE_MOUSE_BUTTON_MIDDLE  ::xengine::Button::Middle
