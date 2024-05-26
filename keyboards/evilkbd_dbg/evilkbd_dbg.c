#include "evilkbd_dbg.h"
#include "i2c_master.h"
#include "debug.h"
#include "print.h"
#include "hardware/gpio.h"

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
	// Left
	{{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}},
	{{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
	{{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
	{{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
	// Right
	{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}},
	{{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}},
	{{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}},
	{{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}
};
#endif

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = true;
}

void matrix_scan_user(void) {
    //dprintf("Matrix scan\n");
}
