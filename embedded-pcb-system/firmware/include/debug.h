#ifndef DEBUG_H
#define DEBUG_H

#include "hal.h"

void debug_init(void);
void debug_uart_send_str(const char *str);
void debug_uart_send_num(int32_t num);
void debug_i2c_scan(I2C_TypeDef *i2c);
void debug_bme280_data(float temp, float pres, float hum);
void debug_lsm6ds3_data(lsm6ds3_axis_t accel, lsm6ds3_axis_t gyro);

#endif
