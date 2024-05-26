# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_ENABLE = no
#RGB_MATRIX_DRIVER = WS2812
LTO_ENABLE = yes
BOOTLOADER = rp2040
MCU = RP2040

SPLIT_KEYBOARD = yes

UART_DRIVER_REQUIRED = yes
SERIAL_DRIVER = vendor
#WS2812_DRIVER = vendor
# if firmware size over limit, try this option
# LTO_ENABLE = yes

DEFAULT_FOLDER = evilkeyboard

RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no
