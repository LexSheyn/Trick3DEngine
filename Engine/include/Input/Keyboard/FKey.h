#pragma once

namespace t3d
{
	struct FKey
	{
		// From glfw3.h
		static constexpr int32 Unknown            = -1;
		
		// Printable keys
		static constexpr int32 Space              = 32;
		static constexpr int32 Apostrophe         = 39;  // < ' >
		static constexpr int32 Comma              = 44;  // < , >
		static constexpr int32 Minus              = 45;  // < - >
		static constexpr int32 Period             = 46;  // < . >
		static constexpr int32 Slash              = 47;  // < / >
		static constexpr int32 Num_0              = 48;
		static constexpr int32 Num_1              = 49;
		static constexpr int32 Num_2              = 50;
		static constexpr int32 Num_3              = 51;
		static constexpr int32 Num_4              = 52;
		static constexpr int32 Num_5              = 53;
		static constexpr int32 Num_6              = 54;
		static constexpr int32 Num_7              = 55;
		static constexpr int32 Num_8              = 56;
		static constexpr int32 Num_9              = 57;
		static constexpr int32 Semicolon          = 59;  // < ; >
		static constexpr int32 Equal              = 61;  // < = >
		static constexpr int32 A                  = 65;
		static constexpr int32 B                  = 66;
		static constexpr int32 C                  = 67;
		static constexpr int32 D                  = 68;
		static constexpr int32 E                  = 69;
		static constexpr int32 F                  = 70;
		static constexpr int32 G                  = 71;
		static constexpr int32 H                  = 72;
		static constexpr int32 I                  = 73;
		static constexpr int32 J                  = 74;
		static constexpr int32 K                  = 75;
		static constexpr int32 L                  = 76;
		static constexpr int32 M                  = 77;
		static constexpr int32 N                  = 78;
		static constexpr int32 O                  = 79;
		static constexpr int32 P                  = 80;
		static constexpr int32 Q                  = 81;
		static constexpr int32 R                  = 82;
		static constexpr int32 S                  = 83;
		static constexpr int32 T                  = 84;
		static constexpr int32 U                  = 85;
		static constexpr int32 V                  = 86;
		static constexpr int32 W                  = 87;
		static constexpr int32 X                  = 88;
		static constexpr int32 Y                  = 89;
		static constexpr int32 Z                  = 90;
		static constexpr int32 LeftBracket        = 91;  // < [ >
		static constexpr int32 BackSlash          = 92;  // < \ >
		static constexpr int32 RightBracket       = 93;  // < ] >
		static constexpr int32 GraveAccent        = 96;  // < ` >
		static constexpr int32 World_1            = 161; // < non-US #1 >
		static constexpr int32 World_2            = 162; // < non-US #2 >
		
		// Function keys
		static constexpr int32 Escape             = 256;
		static constexpr int32 Enter              = 257;
		static constexpr int32 Tab                = 258;
		static constexpr int32 Backspace          = 259;
		static constexpr int32 Insert             = 260;
		static constexpr int32 Delete             = 261;
		static constexpr int32 Right              = 262;
		static constexpr int32 Left               = 263;
		static constexpr int32 Down               = 264;
		static constexpr int32 Up                 = 265;
		static constexpr int32 PageUp             = 266;
		static constexpr int32 PageDown           = 267;
		static constexpr int32 Home               = 268;
		static constexpr int32 End                = 269;
		static constexpr int32 CapsLock           = 280;
		static constexpr int32 ScrollLock         = 281;
		static constexpr int32 NumLock            = 282;
		static constexpr int32 PrintScreen        = 283;
		static constexpr int32 Pause              = 284;
		static constexpr int32 F1                 = 290;
		static constexpr int32 F2                 = 291;
		static constexpr int32 F3                 = 292;
		static constexpr int32 F4                 = 293;
		static constexpr int32 F5                 = 294;
		static constexpr int32 F6                 = 295;
		static constexpr int32 F7                 = 296;
		static constexpr int32 F8                 = 297;
		static constexpr int32 F9                 = 298;
		static constexpr int32 F10                = 299;
		static constexpr int32 F11                = 300;
		static constexpr int32 F12                = 301;
		static constexpr int32 F13                = 302;
		static constexpr int32 F14                = 303;
		static constexpr int32 F15                = 304;
		static constexpr int32 F16                = 305;
		static constexpr int32 F17                = 306;
		static constexpr int32 F18                = 307;
		static constexpr int32 F19                = 308;
		static constexpr int32 F20                = 309;
		static constexpr int32 F21                = 310;
		static constexpr int32 F22                = 311;
		static constexpr int32 F23                = 312;
		static constexpr int32 F24                = 313;
		static constexpr int32 F25                = 314;
		static constexpr int32 KP_0               = 320;
		static constexpr int32 KP_1               = 321;
		static constexpr int32 KP_2               = 322;
		static constexpr int32 KP_3               = 323;
		static constexpr int32 KP_4               = 324;
		static constexpr int32 KP_5               = 325;
		static constexpr int32 KP_6               = 326;
		static constexpr int32 KP_7               = 327;
		static constexpr int32 KP_8               = 328;
		static constexpr int32 KP_9               = 329;
		static constexpr int32 KP_Decimal         = 330;
		static constexpr int32 KP_Divide          = 331;
		static constexpr int32 KP_Multiply        = 332;
		static constexpr int32 KP_Subtract        = 333;
		static constexpr int32 KP_Add             = 334;
		static constexpr int32 KP_Enter           = 335;
		static constexpr int32 KP_Equal           = 336;
		static constexpr int32 LeftShift          = 340;
		static constexpr int32 LeftControl        = 341;
		static constexpr int32 LeftAlt            = 342;
		static constexpr int32 LeftSuper          = 343;
		static constexpr int32 RightShift         = 344;
		static constexpr int32 RightControl       = 345;
		static constexpr int32 RightAlt           = 346;
		static constexpr int32 RightSuper         = 347;
		static constexpr int32 Menu               = 348;
		
		static constexpr int32 Last               = Menu;
	};



// @defgroup mods Modifier key flags
//  @brief Modifier key flags.
//
//  See [key input](@ref input_key) for how these are used.
//
//  @ingroup input

// @brief If this bit is set one or more Shift keys were held down.
//
//  If this bit is set one or more Shift keys were held down.
//
#define T3D_MOD_SHIFT           0x0001
// @brief If this bit is set one or more Control keys were held down.
//
//  If this bit is set one or more Control keys were held down.
//
#define T3D_MOD_CONTROL         0x0002
// @brief If this bit is set one or more Alt keys were held down.
//
//  If this bit is set one or more Alt keys were held down.
//
#define T3D_MOD_ALT             0x0004
// @brief If this bit is set one or more Super keys were held down.
//
//  If this bit is set one or more Super keys were held down.
//
#define T3D_MOD_SUPER           0x0008
// @brief If this bit is set the Caps Lock key is enabled.
//
//  If this bit is set the Caps Lock key is enabled and the @ref
//  T3D_LOCK_KEY_MODS input mode is set.
//
#define T3D_MOD_CAPS_LOCK       0x0010
// @brief If this bit is set the Num Lock key is enabled.
//
//  If this bit is set the Num Lock key is enabled and the @ref
//  T3D_LOCK_KEY_MODS input mode is set.
//
#define T3D_MOD_NUM_LOCK        0x0020
}