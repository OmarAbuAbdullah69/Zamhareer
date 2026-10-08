#include "zm/input.hpp"

namespace zm {
void input::update() {
  mKeyPressed.reset();
  mKeyReleased.reset();

  mMouseButtonPressed.reset();
  mMouseButtonReleased.reset();

  mGamePadButtonPressed.reset();
  mGamePadButtonReleased.reset();
}
void input::listen(event t) {
  switch (t.type) {
  case eventType::MouseMoved:
    mMouseX = t.mouseMove.x;
    mMouseX = t.mouseMove.y;
    break;
  case eventType::MouseScrolled:
    mMouseScrollX = t.mouseScroll.x;
    mMouseScrollY = t.mouseScroll.y;
    break;
    // TODO::
    // I dont know what are the touch stuff are so Complete them.
  case eventType::TouchMoved:
    mTouchID = t.touch.id;
    mTouchX = t.touch.x;
    mTouchY = t.touch.y;
  case eventType::GamepadAxisMoved:
    mGamePadAxies = t.gamepadAxis.axis;
    mGamePadAxiesValue = t.gamepadAxis.value;
    break;
  case eventType::GamepadButtonPressed:
    mGamePadButtonDown[static_cast<int>(t.gamepadButton.button)] = true;
    mGamePadButtonPressed[static_cast<int>(t.gamepadButton.button)] = true;
    break;
  case eventType::GamepadButtonReleased:
    mGamePadButtonDown[static_cast<int>(t.gamepadButton.button)] = false;
    mGamePadButtonReleased[static_cast<int>(t.gamepadButton.button)] = true;
    break;
  case eventType::MouseButtonPressed:
    mMouseButtonDown[static_cast<int>(t.gamepadButton.button)] = true;
    mMouseButtonPressed[static_cast<int>(t.gamepadButton.button)] = true;
    break;
  case eventType::MouseButtonReleased:
    mMouseButtonDown[static_cast<int>(t.gamepadButton.button)] = false;
    mMouseButtonReleased[static_cast<int>(t.gamepadButton.button)] = true;
    break;
  case eventType::KeyPressed:
    mKeyDown[static_cast<int>(t.gamepadButton.button)] = true;
    mKeyPressed[static_cast<int>(t.gamepadButton.button)] = true;
    break;
  case eventType::KeyReleased:
    mKeyDown[static_cast<int>(t.gamepadButton.button)] = false;
    mKeyReleased[static_cast<int>(t.gamepadButton.button)] = true;
    break;
  default:
    break;
  }
}
} // namespace zm
