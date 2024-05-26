// Copyright 2024 Jack Hamilton (@jackhamilton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// #define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP23
#define SERIAL_USART_RX_PIN GP20
#define UART_TX_PIN GP23
#define UART_RX_PIN GP20

#define I2C1_SDA_PIN GP28
#define I2C1_SCL_PIN GP29
#define OLED_ADDRESS 0x3C
#define OLED_DISPLAY_128X32
#define OLED_TIMEOUT 30000  // Timeout in milliseconds
#define OLED_BRIGHTNESS 128 // Set brightness level

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
