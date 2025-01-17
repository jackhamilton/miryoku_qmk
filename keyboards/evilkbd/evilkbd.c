#include "evilkbd.h"
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

void keyboard_pre_init_kb(void) {
    debug_enable = true;
    debug_matrix = true;

    dprint("Initializing I2C\n");
    i2c_init();
    dprint("I2C initialized.\n");

    // Call the user-defined pre-init function
    keyboard_pre_init_user();
}

 void i2c_init(void) {
     gpio_set_pin_input(GP28);
     gpio_set_pin_input(GP29);
     wait_ms(10);

     palSetPadMode(GPIO, 28, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B6 to I2C function
     palSetPadMode(GPIO, 29, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B7 to I2C function
 }


// void i2c_init(void) {
//     // Initialize the I2C pins for the RP2040
//     gpio_init(I2C1_SDA_PIN);
//     gpio_set_dir(I2C1_SDA_PIN, GPIO_IN);
//     gpio_pull_up(I2C1_SDA_PIN);
//
//     gpio_init(I2C1_SCL_PIN);
//     gpio_set_dir(I2C1_SCL_PIN, GPIO_IN);
//     gpio_pull_up(I2C1_SCL_PIN);
//
//     // Add a small delay to stabilize the pins
//     wait_ms(10);
//
//     // Set the pins to their I2C function
//     gpio_set_function(I2C1_SDA_PIN, GPIO_FUNC_I2C);
//     gpio_set_function(I2C1_SCL_PIN, GPIO_FUNC_I2C);
// }
