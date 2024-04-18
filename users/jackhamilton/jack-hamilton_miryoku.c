// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <stdint.h>
#include "features/achordion.h"
#include QMK_KEYBOARD_H

#ifdef OS_DETECTION_ENABLE
  #include "os_detection.h"
#endif

#include "jack-hamilton_miryoku.h"

// -- MANNA HARBOUR MIRYOKU
enum {
    U_TD_BOOT,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
    MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        reset_keyboard();
    }
}

#define MIRYOKU_X(LAYER, STRING)                                        \
    void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
        if (state->count == 2) {                                        \
            default_layer_set((layer_state_t)1 << U_##LAYER);           \
        }                                                               \
    }
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X

tap_dance_action_t tap_dance_actions[] = {[U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define MIRYOKU_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
                                          MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

// keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
    MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

// shift functions

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

const key_override_t **key_overrides = (const key_override_t *[]){&capsword_key_override, NULL};

// JACK HAMILTON CUSTOMIZATION LAYER
// perkey hold
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) {
        return false;
    }

    switch (keycode) {
    case KC_AGIN:
        if (record->event.pressed) {
            os_variant_t detected_os = detected_host_os();
            switch (detected_os) {
                case OS_MACOS:
                case OS_IOS:
                    SEND_STRING(SS_LCMD("z")); // selects all and copies
                    break;
                case OS_WINDOWS:
                case OS_LINUX:
                case OS_UNSURE:
                    SEND_STRING(SS_LCTL("y"));
                    break;
            }
        }
        break;
    case KC_PSTE:
        if (record->event.pressed) {
            os_variant_t detected_os = detected_host_os();
            switch (detected_os) {
                case OS_MACOS:
                case OS_IOS:
                    SEND_STRING(SS_LCMD("v")); // selects all and copies
                    break;
                case OS_WINDOWS:
                case OS_LINUX:
                case OS_UNSURE:
                    SEND_STRING(SS_LCTL("v"));
                    break;
            }
        }
        break;
    case KC_COPY:
        if (record->event.pressed) {
            os_variant_t detected_os = detected_host_os();
            switch (detected_os) {
                case OS_MACOS:
                case OS_IOS:
                    SEND_STRING(SS_LCMD("c")); // selects all and copies
                    break;
                case OS_WINDOWS:
                case OS_LINUX:
                case OS_UNSURE:
                    SEND_STRING(SS_LCTL("c"));
                    break;
            }
        }
        break;
    case KC_CUT:
        if (record->event.pressed) {
            os_variant_t detected_os = detected_host_os();
            switch (detected_os) {
                case OS_MACOS:
                case OS_IOS:
                    SEND_STRING(SS_LCMD("x")); // selects all and copies
                    break;
                case OS_WINDOWS:
                case OS_LINUX:
                case OS_UNSURE:
                    SEND_STRING(SS_LCTL("x"));
                    break;
            }
        }
        break;
    case KC_UNDO:
        if (record->event.pressed) {
            os_variant_t detected_os = detected_host_os();
            switch (detected_os) {
                case OS_MACOS:
                case OS_IOS:
                    SEND_STRING(SS_LCMD("z")); // selects all and copies
                    break;
                case OS_WINDOWS:
                case OS_LINUX:
                case OS_UNSURE:
                    SEND_STRING(SS_LCTL("z"));
                    break;
            }
        }
        break;
    }
    return true;
};

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(U_MEDIA, KC_ESC):
            return true;
        case LT(U_NAV, KC_SPC):
            return true;
        case LT(U_MOUSE, KC_TAB):
            return true;
        case LT(U_SYM, KC_ENT):
            return true;
        case LT(U_NUM, KC_BSPC):
            return true;
        case LT(U_FUN, KC_DEL):
            return true;
        case LSFT_T(KC_F):
            return true;
        case LSFT_T(KC_J):
            return true;
        case LSFT_T(KC_S):
            return true;
        case LSFT_T(KC_N):
            return true;
        default:
            return false;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
  // If you quickly hold a tap-hold key after tapping it, the tap action is
  // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
  // lead to missed triggers in fast typing. Here, returning 0 means we
  // instead want to "force hold" and disable key repeating.
  switch (keycode) {
    case KC_TAB:
    case KC_SPACE:
      return QUICK_TAP_TERM;  // Enable key repeating.
    default:
      return 0;  // Otherwise, force hold and disable key repeating.
  }
}

void matrix_scan_user(void) {
    achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
    if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 3) {
        return true;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

// bool process_detected_host_os_user(os_variant_t detected_os) {
//     extern keymap_config_t keymap_config;
//     switch (detected_os) {
//         case OS_MACOS:
//         case OS_IOS:
//             keymap_config.swap_lctl_lgui = true;
//             break;
//         case OS_WINDOWS:
//             break;
//         case OS_LINUX:
//             break;
//         case OS_UNSURE:
//             break;
//     }
//
//     return true;
// }

#ifdef OLED_ENABLE
enum layers { BASE, EXTRA, TAP, BUTTON, NAV, MOUSE, MEDIA, NUM, SYM, FUN };

bool render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_write_P(PSTR("BASE"), false);
            break;
        case BUTTON:
            oled_write_P(PSTR("BUTTON"), false);
            break;
        case MEDIA:
            oled_write_P(PSTR("MEDIA"), false);
            break;
        case NAV:
            oled_write_P(PSTR("NAV"), false);
            break;
        case MOUSE:
            oled_write_P(PSTR("MOUSE"), false);
            break;
        case SYM:
            oled_write_P(PSTR("SYM"), false);
            break;
        case NUM:
            oled_write_P(PSTR("NUM"), false);
            break;
        case FUN:
            oled_write_P(PSTR("FUN"), false);
            break;
        case TAP:
            oled_write_P(PSTR("TAP"), false);
            break;
        case EXTRA:
            oled_write_P(PSTR("EXTRA"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_P(PSTR("NONE"), false);
    }

    os_variant_t detected_os = detected_host_os();
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            oled_write_P(PSTR("\nMacOS Bindings"), false);
            break;
        case OS_WINDOWS:
            oled_write_P(PSTR("\nWindows Bindings"), false);
            break;
        case OS_LINUX:
            oled_write_P(PSTR("\nLinux Bindings"), false);
            break;
        case OS_UNSURE:
            oled_write_P(PSTR("\nDefault Bindings"), false);
            break;
    }

    oled_write_P(PSTR("\nDriver: Jack Hamilton"), false);
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(qmk_logo, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }

    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();      // Renders a static logo
        oled_scroll_left(); // Turns on scrolling
    }
    return false;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }
}

#endif
