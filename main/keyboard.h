#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <driver/gpio.h>

const gpio_num_t matrix_row_pins[] = {
    GPIO_NUM_18,
    GPIO_NUM_5,
    GPIO_NUM_17,
    GPIO_NUM_16};
const gpio_num_t matrix_col_pins[] = {
    GPIO_NUM_4,
    GPIO_NUM_0,
    GPIO_NUM_2,
    GPIO_NUM_15};

int matrix_states[4][4] = {0};

void matrix_init(void);

void matrix_scan(void);

#endif // __KEYBOARD_H__
