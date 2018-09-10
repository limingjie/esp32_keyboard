#include "keyboard.h"

static const gpio_num_t matrix_row_pins[] = {
    GPIO_NUM_16,
    GPIO_NUM_17};

static const gpio_num_t matrix_col_pins[] = {
    GPIO_NUM_2,
    GPIO_NUM_0,
    GPIO_NUM_4};

static int matrix_states[2][3] = {0};

static uint8_t keycodes[2][3] = {
    {HID_KEY_A, HID_KEY_B, HID_KEY_C},
    {HID_KEY_D, HID_KEY_E, HID_KEY_F}
};

static uint8_t kc_q[256] = {0}; // 6KRO, but make sure there is always a zero at the end of the queue.
static int kc_q_size = 0;

void matrix_init(void)
{
    // Init GPIO pins
    for (int row = 0; row < 2; row++)
    {
        gpio_pad_select_gpio(matrix_row_pins[row]);
        gpio_set_direction(matrix_row_pins[row], GPIO_MODE_INPUT_OUTPUT);
        gpio_set_drive_capability(matrix_row_pins[row], GPIO_DRIVE_CAP_0);
        gpio_set_level(matrix_row_pins[row], 0);
    }
    for (int col = 0; col < 3; col++)
    {
        gpio_pad_select_gpio(matrix_col_pins[col]);
        gpio_set_direction(matrix_col_pins[col], GPIO_MODE_INPUT_OUTPUT);
        gpio_set_level(matrix_col_pins[col], 0);
    }
}

void send_keycode(uint16_t hid_conn_id, uint8_t keycode, bool pressed)
{
    if (pressed)
    {
        kc_q[kc_q_size++] = keycode;
    }
    else
    {
        for (int i = 0; i < kc_q_size; i++)
        {
            if (kc_q[i] == keycode)
            {
                for (int j = i; j < kc_q_size; j++)
                {
                    kc_q[j] = kc_q[j+1];
                }
                kc_q_size--;
                break;
            }
        }
    }

    ESP_LOGI("ESP32 Keyboard", "%d %d %d %d %d %d", kc_q[0], kc_q[1], kc_q[2], kc_q[3], kc_q[4], kc_q[5]);

    esp_hidd_send_keyboard_value(hid_conn_id, 0, kc_q, (kc_q_size > 6) ? 6 : kc_q_size);
}

void matrix_scan(uint16_t hid_conn_id)
{
    for (int col = 0; col < 3; col++)
    {
        gpio_set_level(matrix_col_pins[col], 1);
        for (int row = 0; row < 2; row++)
        {
            int state = gpio_get_level(matrix_row_pins[row]);
            if (matrix_states[row][col] != state)
            {
                ESP_LOGI("ESP32 Keyboard", "%s, (%d, %d), %s", __func__, row, col, (state == 1) ? "keydown" : "keyup");
                matrix_states[row][col] = state;
                // esp_hidd_send_consumer_value(hid_conn_id, keycodes[row][col], state == 1);

                send_keycode(hid_conn_id, keycodes[row][col], (state == 1));
                // uint8_t key_value = (state == 1) ? keycodes[row][col] : 0;
                // esp_hidd_send_keyboard_value(hid_conn_id, 0, &key_value, 1);
            }
        }
        gpio_set_level(matrix_col_pins[col], 0);
    }
}
