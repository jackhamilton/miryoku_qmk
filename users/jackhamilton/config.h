// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include "custom_config.h"

// default but used in macros
#undef TAPPING_TERM
#define TAPPING_TERM 150

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// #define QUICK_TAP_TERM 150
//#define QUICK_TAP_TERM_PER_KEY
#define QUICK_TAP_TERM 0

#define PERMISSIVE_HOLD_PER_KEY
#define ACHORDION_STREAK


// Auto Shift
// #define NO_AUTO_SHIFT_ALPHA
// #define AUTO_SHIFT_TIMEOUT TAPPING_TERM
// #define AUTO_SHIFT_NO_SETUP

#define MIRYOKU_CLIPBOARD_FUN

#define RGBLIGHT_SLEEP
#undef RGBLIGHT_DEFAULT_VAL
#define RGBLIGHT_DEFAULT_VAL 120
#undef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 120

#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE

// Mouse key speed and acceleration.
// #undef MOUSEKEY_DELAY
// #define MOUSEKEY_DELAY 0
// #undef MOUSEKEY_INTERVAL
// #define MOUSEKEY_INTERVAL 16
// #undef MOUSEKEY_WHEEL_DELAY
// #define MOUSEKEY_WHEEL_DELAY 0
// #undef MOUSEKEY_MAX_SPEED
// #define MOUSEKEY_MAX_SPEED 6
// #undef MOUSEKEY_TIME_TO_MAX
// #define MOUSEKEY_TIME_TO_MAX 64

// Thumb Combos
#if defined(MIRYOKU_KLUDGE_THUMBCOMBOS)
#    define COMBO_COUNT 8
#    define COMBO_TERM 200
#    define EXTRA_SHORT_COMBOS
#endif

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
