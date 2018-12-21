#pragma once
#include <functional>
#include <memory>
#include <string>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif __APPLE__
#include <CoreGraphics/CGRemoteOperation.h>
#elif __linux__
#include <X11/Xlib.h>
#else
#error "Unknown Operating System!"
#endif

#if defined(WINDOWS) || defined(WIN32)
#if defined(INPUT_LITE_DLL)
#define INPUT_LITE_EXTERN __declspec(dllexport)
#else
#define INPUT_LITE_EXTERN
#endif
#else
#define INPUT_LITE_EXTERN
#endif

namespace SL {
namespace Input_Lite {
// codes are from http://www.usb.org/developers/hidpage/Hut1_12v2.pdf
enum KeyCodes : unsigned char {
  KEY_A = 4,
  KEY_B = 5,
  KEY_C = 6,
  KEY_D = 7,
  KEY_E = 8,
  KEY_F = 9,
  KEY_G = 10,
  KEY_H = 11,
  KEY_I = 12,
  KEY_J = 13,
  KEY_K = 14,
  KEY_L = 15,
  KEY_M = 16,
  KEY_N = 17,
  KEY_O = 18,
  KEY_P = 19,
  KEY_Q = 20,
  KEY_R = 21,
  KEY_S = 22,
  KEY_T = 23,
  KEY_U = 24,
  KEY_V = 25,
  KEY_W = 26,
  KEY_X = 27,
  KEY_Y = 28,
  KEY_Z = 29,
  KEY_1 = 30,
  KEY_2 = 31,
  KEY_3 = 32,
  KEY_4 = 33,
  KEY_5 = 34,
  KEY_6 = 35,
  KEY_7 = 36,
  KEY_8 = 37,
  KEY_9 = 38,
  KEY_0 = 39,
  KEY_Enter = 40,
  KEY_Escape = 41,
  KEY_Backspace = 42,
  KEY_Tab = 43,
  KEY_Space = 44,
  KEY_Minus = 45,
  KEY_Equals = 46,
  KEY_LeftBracket = 47,
  KEY_RightBracket = 48,
  KEY_Backslash = 49,
  KEY_Semicolon = 51,
  KEY_Quote = 52,
  KEY_Grave = 53,
  KEY_Comma = 54,
  KEY_Period = 55,
  KEY_Slash = 56,
  KEY_CapsLock = 57,
  KEY_F1 = 58,
  KEY_F2 = 59,
  KEY_F3 = 60,
  KEY_F4 = 61,
  KEY_F5 = 62,
  KEY_F6 = 63,
  KEY_F7 = 64,
  KEY_F8 = 65,
  KEY_F9 = 66,
  KEY_F10 = 67,
  KEY_F11 = 68,
  KEY_F12 = 69,
  KEY_PrintScreen = 70,
  KEY_ScrollLock = 71,
  KEY_Pause = 72,
  KEY_Insert = 73,
  KEY_Home = 74,
  KEY_PageUp = 75,
  KEY_Delete = 76,
  KEY_End = 77,
  KEY_PageDown = 78,
  KEY_Right = 79,
  KEY_Left = 80,
  KEY_Down = 81,
  KEY_Up = 82,
  KP_NumLock = 83,
  KP_Divide = 84,
  KP_Multiply = 85,
  KP_Subtract = 86,
  KP_Add = 87,
  KP_Enter = 88,
  KP_1 = 89,
  KP_2 = 90,
  KP_3 = 91,
  KP_4 = 92,
  KP_5 = 93,
  KP_6 = 94,
  KP_7 = 95,
  KP_8 = 96,
  KP_9 = 97,
  KP_0 = 98,
  KP_Point = 99,
  KEY_NonUSBackslash = 100,
  KP_Equals = 103,
  KEY_F13 = 104,
  KEY_F14 = 105,
  KEY_F15 = 106,
  KEY_F16 = 107,
  KEY_F17 = 108,
  KEY_F18 = 109,
  KEY_F19 = 110,
  KEY_F20 = 111,
  KEY_F21 = 112,
  KEY_F22 = 113,
  KEY_F23 = 114,
  KEY_F24 = 115,
  KEY_Help = 117,
  KEY_Menu = 118,
  KEY_LeftControl = 224,
  KEY_LeftShift = 225,
  KEY_LeftAlt = 226,
  KEY_LeftMeta = 227,
  KEY_RightControl = 228,
  KEY_RightShift = 229,
  KEY_RightAlt = 230,
  KEY_RightMeta = 231,
  INVALID = 255
};

enum class MouseButtons : unsigned char { LEFT, MIDDLE, RIGHT };
#ifdef WIN32
INPUT_LITE_EXTERN DWORD ConvertToNative(Input_Lite::KeyCodes key);
INPUT_LITE_EXTERN Input_Lite::KeyCodes ConvertToKeyCode(DWORD key);
#elif __APPLE__
INPUT_LITE_EXTERN CGKeyCode ConvertToNative(KeyCodes key);
INPUT_LITE_EXTERN KeyCodes ConvertToKeyCode(CGKeyCode key);
#elif __linux__
INPUT_LITE_EXTERN KeyCode ConvertToNative(Input_Lite::KeyCodes key);
INPUT_LITE_EXTERN Input_Lite::KeyCodes ConvertToKeyCode(KeyCode key);
#else
#error "Unknown Operating System!"
#endif

struct KeyEvent {
  bool Pressed;
  KeyCodes Key;
};
struct MouseButtonEvent {
  bool Pressed;
  MouseButtons Button;
};
struct MouseScrollEvent {
  int Offset;
};
struct MousePositionOffsetEvent {
  int X = 0;
  int Y = 0;
};
struct MousePositionAbsoluteEvent {
  int X = 0;
  int Y = 0;
};

INPUT_LITE_EXTERN void SendInput(const KeyEvent &e);
INPUT_LITE_EXTERN void SendInput(const MouseButtonEvent &e);
INPUT_LITE_EXTERN void SendInput(const MouseScrollEvent &e);
INPUT_LITE_EXTERN void SendInput(const MousePositionOffsetEvent &e);
INPUT_LITE_EXTERN void SendInput(const MousePositionAbsoluteEvent &e);

class INPUT_LITE_EXTERN IInputManager {
 public:
  virtual ~IInputManager() {}
  virtual bool PushEvent(const KeyEvent &e) = 0;
  virtual bool PushEvent(const MouseButtonEvent &e) = 0;
  virtual bool PushEvent(const MouseScrollEvent &pos) = 0;
  virtual bool PushEvent(const MousePositionOffsetEvent &pos) = 0;
  virtual bool PushEvent(const MousePositionAbsoluteEvent &pos) = 0;
};
class INPUT_LITE_EXTERN IInputConfiguration {
 public:
  virtual ~IInputConfiguration() {}

  virtual std::shared_ptr<IInputConfiguration> onEvent(const std::function<void(const KeyEvent &)>
      &cb) = 0;
  virtual std::shared_ptr<IInputConfiguration> onEvent(const
      std::function<void(const MouseButtonEvent &)> &cb) = 0;
  virtual std::shared_ptr<IInputConfiguration> onEvent(const
      std::function<void(const MouseScrollEvent &)> &cb) = 0;
  virtual std::shared_ptr<IInputConfiguration> onEvent(const
      std::function<void(const MousePositionOffsetEvent &)> &cb) = 0;
  virtual std::shared_ptr<IInputConfiguration> onEvent(const
      std::function<void(const MousePositionAbsoluteEvent &)> &cb) = 0;
  virtual std::shared_ptr<IInputManager> Build() = 0;
};

INPUT_LITE_EXTERN std::shared_ptr<IInputConfiguration> CreateInputConfiguration();
} // namespace Input_Lite
} // namespace SL
