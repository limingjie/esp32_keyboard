#include "keyboard.h"

void matrix_init(void)
{
    // Init gpio pins
    for (int row = 0; row < 4; row++)
    {
        gpio_pad_select_gpio(matrix_row_pins[row]);
		gpio_set_direction(matrix_row_pins[row], GPIO_MODE_INPUT_OUTPUT);
        gpio_set_drive_capability(matrix_row_pins[row], GPIO_DRIVE_CAP_0);
		gpio_set_level(matrix_row_pins[row], 0);
    }
    for (int col = 0; col < 4; col++)
    {
        gpio_pad_select_gpio(matrix_col_pins[col]);
		gpio_set_direction(matrix_col_pins[col], GPIO_MODE_INPUT_OUTPUT);
		gpio_set_level(matrix_col_pins[col], 0);
    }
}

void matrix_scan(void)
{

}

