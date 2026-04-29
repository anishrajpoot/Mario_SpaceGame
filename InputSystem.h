#pragma once

#include <windows.h>

enum KeyCode
{
    // Alphabet Keys
    A = 'A', B = 'B', C = 'C', D = 'D', E = 'E', F = 'F', G = 'G', H = 'H', I = 'I',
    J = 'J', K = 'K', L = 'L', M = 'M', N = 'N', O = 'O', P = 'P', Q = 'Q', R = 'R',
    S = 'S', T = 'T', U = 'U', V = 'V', W = 'W', X = 'X', Y = 'Y', Z = 'Z',

    // Number Keys
    NUM_0 = '0', NUM_1 = '1', NUM_2 = '2', NUM_3 = '3', NUM_4 = '4',
    NUM_5 = '5', NUM_6 = '6', NUM_7 = '7', NUM_8 = '8', NUM_9 = '9',

    // Function Keys
    F1 = VK_F1, F2 = VK_F2, F3 = VK_F3, F4 = VK_F4,
    F5 = VK_F5, F6 = VK_F6, F7 = VK_F7, F8 = VK_F8,
    F9 = VK_F9, F10 = VK_F10, F11 = VK_F11, F12 = VK_F12,

    // Arrow Keys
    UP = VK_UP, DOWN = VK_DOWN, LEFT = VK_LEFT, RIGHT = VK_RIGHT,

    // Control Keys
    ESC = VK_ESCAPE, TAB = VK_TAB, ENTER = VK_RETURN, SPACE = VK_SPACE,
    BACKSPACE = VK_BACK, DEL = VK_DELETE, LSHIFT = VK_LSHIFT, RSHIFT = VK_RSHIFT, 
    LCTRL = VK_LCONTROL, RCTRL = VK_RCONTROL, LALT = VK_LMENU, RALT = VK_RMENU,

    // Miscellaneous keys
    HOME = VK_HOME, END = VK_END, PAGEUP = VK_PRIOR, PAGEDOWN = VK_NEXT,
    INSERT = VK_INSERT, PAUSE = VK_PAUSE, PRINTSCREEN = VK_SNAPSHOT,

    // Special keys
    CAPSLOCK = VK_CAPITAL, SCROLL_LOCK = VK_SCROLL, NUMLOCK = VK_NUMLOCK,
};

class Input
{
public:
    // Checks Keypress Once And Again Only After If The Key Is Uplifted And Pressed Again
    static bool GetKeyDown(KeyCode key)
    {
        // Ensure the static array for key states is unique to this method
        static bool keyState[256] = { false };

        bool currentlyPressed = GetKey(key);
        bool wasPressed = keyState[static_cast<int>(key)];

        // Update the state
        keyState[static_cast<int>(key)] = currentlyPressed;

        // Return true if it was not pressed before but is now pressed
        return !wasPressed && currentlyPressed;
    }

    // Checks Key Press Every Time
    static bool GetKey(KeyCode key)
    {
        return (GetKeyState(static_cast<int>(key)) & 0x8000) != 0;
    }

    // Checks Whether The Key Is Uplifted Or Not
    static bool GetKeyUp(KeyCode key)
    {
        static bool keyState[256] = { false };

        bool currentlyPressed = GetKey(key);
        bool wasPressed = keyState[static_cast<int>(key)];

        // Update the state
        keyState[static_cast<int>(key)] = currentlyPressed;

        return wasPressed && !currentlyPressed;
    }
};

