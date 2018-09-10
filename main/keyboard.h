#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <driver/gpio.h>
#include "esp_hidd_prf_api.h"
#include "esp_log.h"
#include "hid_dev.h"

void matrix_init(void);

void matrix_scan(uint16_t hid_conn_id);

#endif // __KEYBOARD_H__
