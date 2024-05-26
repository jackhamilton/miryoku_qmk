// Copyright 2024 Jack Hamilton (@jackhamilton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define I2C1_SDA_PIN GP28
#define I2C1_SCL_PIN GP29
#define OLED_ADDRESS 0x3C
#define OLED_DISPLAY_128X32
#define OLED_TIMEOUT 30000  // Timeout in milliseconds
#define OLED_BRIGHTNESS 128 // Set brightness level

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
