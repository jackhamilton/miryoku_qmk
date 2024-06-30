// Copyright 2022 Manna Harbour
//
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <stdint.h>
// #include "features/achordion.h"
#include QMK_KEYBOARD_H

#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
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

layer_state_t tapDanceLayer = (layer_state_t)1;

#define MIRYOKU_X(LAYER, STRING)                                        \
    void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
        if (state->count == 2) {                                        \
            tapDanceLayer = (layer_state_t)1 << U_##LAYER;              \
            default_layer_set(tapDanceLayer);                           \
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
// const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//    {19, 3, HSV_RED},       // Light 4 LEDs, starting with LED 6
//    {40, 3, HSV_RED}       // Light 4 LEDs, starting with LED 12
//);
//// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
// const rgblight_segment_t PROGMEM my_colemak_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {1, 18, HSV_CYAN},
//     {22, 18, HSV_CYAN}
//);
//// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
// const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {1, 18, HSV_YELLOW},
//     {22, 18, HSV_YELLOW}
//);
//
// const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
//     my_capslock_layer,
//     my_colemak_layer,    // Overrides caps lock layer
//     my_qwerty_layer    // Overrides other layers
//);
//
// void keyboard_post_init_user(void) {
//     // Enable the LED layers
//     rgblight_layers = my_rgb_layers;
// }

struct os_keybind {
    int   keycode;
    char *macBind;
    char *normalBind;
};

const struct os_keybind keybinds[] = {{KC_AGIN, SS_LCMD("y"), SS_LCTL("y")}, {KC_PSTE, SS_LCMD("v"), SS_LCTL("v")}, {KC_COPY, SS_LCMD("c"), SS_LCTL("c")}, {KC_CUT, SS_LCMD("x"), SS_LCTL("x")}, {KC_UNDO, SS_LCMD("z"), SS_LCTL("z")}};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // if (!process_achordion(keycode, record)) {
    //     return false;
    // }
    os_variant_t detected_os = detected_host_os();
    size_t       size        = sizeof(keybinds) / sizeof(keybinds[0]);
    for (int i = 0; i < size; i += 1) {
        struct os_keybind current = keybinds[i];
        if (keycode == current.keycode) {
            if (record->event.pressed) {
                switch (detected_os) {
                    case OS_MACOS:
                    case OS_IOS:
                        send_string(current.macBind); // selects all and copies
                        break;
                    case OS_WINDOWS:
                    case OS_LINUX:
                    case OS_UNSURE:
                        send_string(current.normalBind);
                        break;
                }
                return false;
            }
        }
    }
    return true;
};

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
            // colemak
        case LSFT_T(KC_T):
        case LSFT_T(KC_N):
            // qwerty
        case LSFT_T(KC_F):
        case LSFT_T(KC_J):
            return true;
        default:
            return false;
    }
}

// uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
//   // If you quickly hold a tap-hold key after tapping it, the tap action is
//   // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
//   // lead to missed triggers in fast typing. Here, returning 0 means we
//   // instead want to "force hold" and disable key repeating.
//   switch (keycode) {
//     case LT(U_MOUSE,KC_TAB):
//     case LT(U_NAV,KC_SPACE):
//       return QUICK_TAP_TERM;  // Enable key repeating.
//     default:
//       return 0;  // Otherwise, force hold and disable key repeating.
//   }
// }

// void matrix_scan_user(void) {
//     achordion_task();
// }
//
// bool achordion_chord(uint16_t tap_hold_keycode,
//                      keyrecord_t* tap_hold_record,
//                      uint16_t other_keycode,
//                      keyrecord_t* other_record) {
//     if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 3) {
//         return true;
//     }
//
//     return achordion_opposite_hands(tap_hold_record, other_record);
// }

enum layers { BASE, EXTRA, TAP, BUTTON, NAV, /* MOUSE, */ MEDIA, NUM, SYM, FUN };

#define COLEMAK 1
#define QWERTY 2
#define GAMING 4
void update_layer_led(void) {
    led_t led_state = host_keyboard_led_state();
    if (!led_state.caps_lock && !is_caps_word_on()) {
        switch (get_highest_layer(layer_state)) {
            case MEDIA:
                rgblight_sethsv(HSV_DIM_WHITE);
                rgblight_sethsv_range(HSV_DIM_CYAN, 0, 26);
                break;
            case NAV:
                rgblight_sethsv(HSV_DIM_PURPLE);
                rgblight_sethsv_range(HSV_DIM_CYAN, 0, 26);
                break;
            case SYM:
                rgblight_sethsv_range(HSV_DIM_PURPLE, 0, 26);
                break;
            case NUM:
                rgblight_sethsv_range(HSV_DIM_PINK, 0, 26);
                break;
            case FUN:
                rgblight_sethsv_range(HSV_DIM_WHITE, 0, 26);
                break;
            default:
                switch (tapDanceLayer) {
                    case COLEMAK:
                        rgblight_sethsv(HSV_DIM_CYAN);
                        break;
                    case QWERTY:
                        rgblight_sethsv(HSV_DIM_YELLOW);
                        break;
                    case GAMING:
                        rgblight_sethsv(HSV_DIM_GREEN);
                        break;
                    default:
                        break;
                }
        }
    }
}

void caps_word_set_user(bool active) {
    if (active) {
        rgblight_sethsv(HSV_DIM_RED);
    } else {
        update_layer_led();
    }
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        rgblight_sethsv(HSV_DIM_RED);
    } else {
        update_layer_led();
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    update_layer_led();
    return state;
}

#ifdef OLED_ENABLE
bool render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case BASE:
            switch (tapDanceLayer) {
                case COLEMAK:
                    oled_write_P(PSTR("COLEMAK"), false);
                    break;
                case QWERTY:
                    oled_write_P(PSTR("QWERTY"), false);
                    break;
                case GAMING:
                    oled_write_P(PSTR("GAMING"), false);
                    break;
                default:
                    break;
            }
            break;
        case MEDIA:
            oled_write_P(PSTR("MEDIA"), false);
            break;
        case NAV:
            oled_write_P(PSTR("NAV"), false);
            break;
            //         case MOUSE:
            //             oled_write_P(PSTR("MOUSE"), false);
            //             break;
        case SYM:
            oled_write_P(PSTR("SYM"), false);
            break;
        case NUM:
            oled_write_P(PSTR("NUM"), false);
            break;
        case FUN:
            oled_write_P(PSTR("FUN"), false);
            break;
        default: {
            char str[8];
            sprintf(str, "%d:%d", tapDanceLayer, get_highest_layer(layer_state));
            oled_write(str, false);
        } break;
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
    oled_write_P(led_state.caps_lock || is_caps_word_on() ? PSTR("CAP ") : PSTR("    "), false);
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
