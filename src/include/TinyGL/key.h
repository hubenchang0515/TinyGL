#ifndef _TINYGL_KEY_H
#define _TINYGL_KEY_H

typedef enum TinyGL_KeyState tiny_keystate_t;
typedef enum TinyGL_Key tiny_key_t;

enum TinyGL_KeyState
{
    TINYGL_KEY_RELEASE = 0,
    TINYGL_KEY_PRESS = 1,
    TINYGL_KEY_REPEAT = 2,
};

// https://www.glfw.org/docs/3.3/group__keys.html
enum TinyGL_Key
{
    TINYGL_KEY_SPACE = 32,
    
    TINYGL_KEY_APOSTROPHE = 39, /* ' */
    
    TINYGL_KEY_COMMA = 44, /* , */
    
    TINYGL_KEY_MINUS = 45, /* - */
    
    TINYGL_KEY_PERIOD = 46, /* . */
    
    TINYGL_KEY_SLASH = 47, /* / */
    
    TINYGL_KEY_0 = 48,
    
    TINYGL_KEY_1 = 49,
    
    TINYGL_KEY_2 = 50,
    
    TINYGL_KEY_3 = 51,
    
    TINYGL_KEY_4 = 52,
    
    TINYGL_KEY_5 = 53,
    
    TINYGL_KEY_6 = 54,
    
    TINYGL_KEY_7 = 55,
    
    TINYGL_KEY_8 = 56,
    
    TINYGL_KEY_9 = 57,
    
    TINYGL_KEY_SEMICOLON = 59, /* ; */
    
    TINYGL_KEY_EQUAL = 61, /* = */
    
    TINYGL_KEY_A = 65,
    
    TINYGL_KEY_B = 66,
    
    TINYGL_KEY_C = 67,
    
    TINYGL_KEY_D = 68,
    
    TINYGL_KEY_E = 69,
    
    TINYGL_KEY_F = 70,
    
    TINYGL_KEY_G = 71,
    
    TINYGL_KEY_H = 72,
    
    TINYGL_KEY_I = 73,
    
    TINYGL_KEY_J = 74,
    
    TINYGL_KEY_K = 75,
    
    TINYGL_KEY_L = 76,
    
    TINYGL_KEY_M = 77,
    
    TINYGL_KEY_N = 78,
    
    TINYGL_KEY_O = 79,
    
    TINYGL_KEY_P = 80,
    
    TINYGL_KEY_Q = 81,
    
    TINYGL_KEY_R = 82,
    
    TINYGL_KEY_S = 83,
    
    TINYGL_KEY_T = 84,
    
    TINYGL_KEY_U = 85,
    
    TINYGL_KEY_V = 86,
    
    TINYGL_KEY_W = 87,
    
    TINYGL_KEY_X = 88,
    
    TINYGL_KEY_Y = 89,
    
    TINYGL_KEY_Z = 90,
    
    TINYGL_KEY_LEFT_BRACKET = 91, /* [ */
    
    TINYGL_KEY_BACKSLASH = 92, /* \ */
    
    TINYGL_KEY_RIGHT_BRACKET = 93, /* ] */
    
    TINYGL_KEY_GRAVE_ACCENT = 96, /* ` */
    
    TINYGL_KEY_WORLD_1 = 161, /* non-US #1 */
    
    TINYGL_KEY_WORLD_2 = 162, /* non-US #2 */
    
    TINYGL_KEY_ESCAPE = 256,
    
    TINYGL_KEY_ENTER = 257,
    
    TINYGL_KEY_TAB = 258,
    
    TINYGL_KEY_BACKSPACE = 259,
    
    TINYGL_KEY_INSERT = 260,
    
    TINYGL_KEY_DELETE = 261,
    
    TINYGL_KEY_RIGHT = 262,
    
    TINYGL_KEY_LEFT = 263,
    
    TINYGL_KEY_DOWN = 264,
    
    TINYGL_KEY_UP = 265,
    
    TINYGL_KEY_PAGE_UP = 266,
    
    TINYGL_KEY_PAGE_DOWN = 267,
    
    TINYGL_KEY_HOME = 268,
    
    TINYGL_KEY_END = 269,
    
    TINYGL_KEY_CAPS_LOCK = 280,
    
    TINYGL_KEY_SCROLL_LOCK = 281,
    
    TINYGL_KEY_NUM_LOCK = 282,
    
    TINYGL_KEY_PRINT_SCREEN = 283,
    
    TINYGL_KEY_PAUSE = 284,
    
    TINYGL_KEY_F1 = 290,
    
    TINYGL_KEY_F2 = 291,
    
    TINYGL_KEY_F3 = 292,
    
    TINYGL_KEY_F4 = 293,
    
    TINYGL_KEY_F5 = 294,
    
    TINYGL_KEY_F6 = 295,
    
    TINYGL_KEY_F7 = 296,
    
    TINYGL_KEY_F8 = 297,
    
    TINYGL_KEY_F9 = 298,
    
    TINYGL_KEY_F10 = 299,
    
    TINYGL_KEY_F11 = 300,
    
    TINYGL_KEY_F12 = 301,
    
    TINYGL_KEY_F13 = 302,
    
    TINYGL_KEY_F14 = 303,
    
    TINYGL_KEY_F15 = 304,
    
    TINYGL_KEY_F16 = 305,
    
    TINYGL_KEY_F17 = 306,
    
    TINYGL_KEY_F18 = 307,
    
    TINYGL_KEY_F19 = 308,
    
    TINYGL_KEY_F20 = 309,
    
    TINYGL_KEY_F21 = 310,
    
    TINYGL_KEY_F22 = 311,
    
    TINYGL_KEY_F23 = 312,
    
    TINYGL_KEY_F24 = 313,
    
    TINYGL_KEY_F25 = 314,
    
    TINYGL_KEY_KP_0 = 320,
    
    TINYGL_KEY_KP_1 = 321,
    
    TINYGL_KEY_KP_2 = 322,
    
    TINYGL_KEY_KP_3 = 323,
    
    TINYGL_KEY_KP_4 = 324,
    
    TINYGL_KEY_KP_5 = 325,
    
    TINYGL_KEY_KP_6 = 326,
    
    TINYGL_KEY_KP_7 = 327,
    
    TINYGL_KEY_KP_8 = 328,
    
    TINYGL_KEY_KP_9 = 329,
    
    TINYGL_KEY_KP_DECIMAL = 330,
    
    TINYGL_KEY_KP_DIVIDE = 331,
    
    TINYGL_KEY_KP_MULTIPLY = 332,
    
    TINYGL_KEY_KP_SUBTRACT = 333,
    
    TINYGL_KEY_KP_ADD = 334,
    
    TINYGL_KEY_KP_ENTER = 335,
    
    TINYGL_KEY_KP_EQUAL = 336,
    
    TINYGL_KEY_LEFT_SHIFT = 340,
    
    TINYGL_KEY_LEFT_CONTROL = 341,
    
    TINYGL_KEY_LEFT_ALT = 342,
    
    TINYGL_KEY_LEFT_SUPER = 343,
    
    TINYGL_KEY_RIGHT_SHIFT = 344,
    
    TINYGL_KEY_RIGHT_CONTROL = 345,
    
    TINYGL_KEY_RIGHT_ALT = 346,
    
    TINYGL_KEY_RIGHT_SUPER = 347,
    
    TINYGL_KEY_MENU = 348,

};

#endif // _TINYGL_KEY_H