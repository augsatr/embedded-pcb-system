#ifndef VIRTUAL_I2C_DRIVER_H
#define VIRTUAL_I2C_DRIVER_H

#include "virtual_hal.h"

#define I2C_READ   0x01
#define I2C_WRITE  0x00

#define I2C_OK          0
#define I2C_ERR_NACK    1
#define I2C_ERR_TIMEOUT 2
#define I2C_ERR_BUSY    3

typedef struct {
    I2C_TypeDef *instance;
    uint8_t dev_addr;
    uint32_t timeout;
} i2c_handle_t;

uint8_t i2c_driver_init(i2c_handle_t *hi2c, I2C_TypeDef *instance, uint32_t clock_speed);
uint8_t i2c_driver_write_reg(i2c_handle_t *hi2c, uint8_t reg, uint8_t data);
uint8_t i2c_driver_read_reg(i2c_handle_t *hi2c, uint8_t reg, uint8_t *data);
uint8_t i2c_driver_write_burst(i2c_handle_t *hi2c, uint8_t reg, uint8_t *data, uint16_t len);
uint8_t i2c_driver_read_burst(i2c_handle_t *hi2c, uint8_t reg, uint8_t *data, uint16_t len);
uint8_t i2c_driver_scan_bus(I2C_TypeDef *i2c, uint8_t *found_addrs, uint8_t *count);

#endif
