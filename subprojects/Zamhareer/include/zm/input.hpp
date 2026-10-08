#pragma once

#include "events.hpp"
#include <bitset>

namespace zm {

class input {
public:
  static input &inst() {
    static input i;
    return i;
  }
  void update();

  inline void getMousePos(float &x, float &y) const {
    x = mMouseX;
    y = mMouseY;
  }
  inline void getMouseScroll(float &x, float &y) const {
    x = mMouseScrollX;
    y = mMouseScrollY;
  }
  inline void getTouh(float &x, float &y, int &id) const {
    x = mTouchX;
    y = mTouchY, id = mTouchID;
  }

  inline void getGamePadAxies(int &axies, float &value) const {
    axies = mGamePadAxies;
    value = mGamePadAxiesValue;
  }

  inline bool isKeyPressed(key k) const {
    return mKeyPressed[static_cast<int>(k)];
  }
  inline bool isKeyDown(key k) const { return mKeyDown[static_cast<int>(k)]; }
  inline bool isKeyReleased(key k) const {
    return mKeyReleased[static_cast<int>(k)];
  }

  inline bool isMouseButtonPressed(mouseButton b) const {
    return mMouseButtonPressed[static_cast<int>(b)];
  }
  inline bool isMouseButtonDown(mouseButton b) const {
    return mMouseButtonDown[static_cast<int>(b)];
  }
  inline bool isMouseButtonReleased(mouseButton b) {
    return mMouseButtonReleased[static_cast<int>(b)];
  }

  inline bool isGamePadButtonPressed(gamePadButton b) const {
    return mGamePadButtonPressed[static_cast<int>(b)];
  }
  inline bool isGamePadButtonDown(gamePadButton b) const {
    return mGamePadButtonDown[static_cast<int>(b)];
  }
  inline bool isGamePadButtonReleased(gamePadButton b) {
    return mGamePadButtonReleased[static_cast<int>(b)];
  }

private:
  friend class viewport;
  void listen(event);
  float mMouseX, mMouseY;
  float mMouseScrollX, mMouseScrollY;

  float mTouchX, mTouchY;
  int mTouchID;

  int mGamePadAxies;
  float mGamePadAxiesValue;

  std::bitset<static_cast<int>(key::KeyCount)> mKeyDown;
  std::bitset<static_cast<int>(key::KeyCount)> mKeyPressed;
  std::bitset<static_cast<int>(key::KeyCount)> mKeyReleased;

  std::bitset<static_cast<int>(mouseButton::ButtonCount)> mMouseButtonDown;
  std::bitset<static_cast<int>(mouseButton::ButtonCount)> mMouseButtonPressed;
  std::bitset<static_cast<int>(mouseButton::ButtonCount)> mMouseButtonReleased;

  std::bitset<static_cast<int>(gamePadButton::ButtonCount)> mGamePadButtonDown;
  std::bitset<static_cast<int>(gamePadButton::ButtonCount)>
      mGamePadButtonPressed;
  std::bitset<static_cast<int>(gamePadButton::ButtonCount)>
      mGamePadButtonReleased;
};
} // namespace zm
