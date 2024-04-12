# Copyright 2019 Manna Harbour
# https://github.com/manna-harbour/miryoku

MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
OS_DETECTION_ENABLE = yes

DEFERRED_EXEC_ENABLE = yes

INTROSPECTION_KEYMAP_C = jack-hamilton_miryoku.c # keymaps

BOOTLOADER = caterina
OLED_ENABLE = yes
OLED_TRANSPORT = i2c

RGBLIGHT_ENABLE = yes

include users/jackhamilton/custom_rules.mk

include users/jackhamilton/post_rules.mk
