#pragma once

namespace zm {
enum class eventType {
  WindowCreated,
  WindowClosed,
  WindowResized,
  WindowFocused,
  WindowUnfocused,

  KeyPressed,
	keyRepeat,
  KeyReleased,

  MouseMoved,
  MouseButtonPressed,
  MouseButtonReleased,
  MouseScrolled,

  TouchStarted,
  TouchMoved,
  TouchEnded,

  TextInput,

// TODO
// do the gamePad stuff using glfw

  GamepadButtonPressed,
  GamepadButtonReleased,
  GamepadAxisMoved,

  Quit
};
enum class key : int {
  Unknown = -1,

  Space = 32,

  Apostrophe = 39,
  Comma = 44,
  Minus = 45,
  Period = 46,
  Slash = 47,

  Num0 = 48,
  Num1,
  Num2,
  Num3,
  Num4,
  Num5,
  Num6,
  Num7,
  Num8,
  Num9,

  Semicolon = 59,
  Equal = 61,

  A = 65,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,

  LeftBracket = 91,
  Backslash = 92,
  RightBracket = 93,
  GraveAccent = 96,

  Escape = 256,
  Enter,
  Tab,
  Backspace,
  Insert,
  Delete,
  Right,
  Left,
  Down,
  Up,
  PageUp,
  PageDown,
  Home,
  End,

  CapsLock = 280,
  ScrollLock,
  NumLock,
  PrintScreen,
  Pause,

  F1 = 290,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12,
  F13,
  F14,
  F15,
  F16,
  F17,
  F18,
  F19,
  F20,
  F21,
  F22,
  F23,
  F24,
  F25,

  LeftShift = 340,
  LeftControl,
  LeftAlt,
  LeftSuper,
  RightShift,
  RightControl,
  RightAlt,
  RightSuper,
  Menu,
  KeyCount
};
enum class mouseButton : int {
  Left = 0,
  Right = 1,
  Middle = 2,
  Button4 = 3,
  Button5 = 4,
  Button6 = 5,
  Button7 = 6,
  Button8 = 7,
  ButtonCount
};
enum class mod : int {
  None = 0,
  Shift = 0x0001,
  Ctrl = 0x0002,
  Alt = 0x0004,
  Super = 0x0008,
  CapsLock = 0x0010,
  NumLock = 0x0020
};
// allows to have combination of mods
// shift | ctrl for example
constexpr mod operator|(mod a, mod b) {
  return static_cast<mod>(static_cast<int>(a) | static_cast<int>(b));
}
enum class gamePadButton : int {
  A,
  B,
  X,
  Y,

  LeftBumper,
  RightBumper,

  Back,
  Start,

  Guide,

  LeftStick,
  RightStick,

  DPadUp,
  DPadRight,
  DPadDown,
  DPadLeft,
  ButtonCount
};

//cuuz the keys are the same
#define KEY_GLFW_2_ZM(code) static_cast<key>(code)
#define MOUSEBUTTIN_GLFW_2_ZM(code) static_cast<mouseButton>(code)

struct event {
  eventType type;
  union {
    struct {
      int width;
      int height;
    } windowResize;

    struct {
      key code;
      mod modifiers;
    } key;
		struct {
			unsigned int codepoint;
		}text;
    struct {
      mouseButton button;
      mod modifiers;
    } mouseButton;

    struct {
      float x;
      float y;
    } mouseMove;

    struct {
      float x;
      float y;
    } mouseScroll;

    struct {
      int id;
      float x;
      float y;
    } touch;

    struct {
      gamePadButton button;
    } gamepadButton;

    struct {
      int axis;
      float value;
    } gamepadAxis;
  };
};}
