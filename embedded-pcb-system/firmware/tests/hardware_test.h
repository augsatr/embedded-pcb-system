#ifndef HARDWARE_TEST_H
#define HARDWARE_TEST_H

#include "hal.h"
#include "i2c_driver.h"
#include "spi_driver.h"
#include "bme280.h"
#include "lsm6ds3.h"

#define TEST_PASS    0
#define TEST_FAIL    1
#define TEST_SKIP    2

typedef struct {
    uint8_t total;
    uint8_t passed;
    uint8_t failed;
    uint8_t skipped;
} test_result_t;

uint8_t test_i2c_bus_scan(I2C_TypeDef *i2c);
uint8_t test_i2c_loopback(void);
uint8_t test_spi_loopback(void);
uint8_t test_bme280_communication(i2c_handle_t *hi2c);
uint8_t test_bme280_temperature(i2c_handle_t *hi2c);
uint8_t test_bme280_pressure(i2c_handle_t *hi2c);
uint8_t test_bme280_humidity(i2c_handle_t *hi2c);
uint8_t test_lsm6ds3_communication(spi_handle_t *hspi);
uint8_t test_lsm6ds3_accelerometer(spi_handle_t *hspi);
uint8_t test_lsm6ds3_gyroscope(spi_handle_t *hspi);
uint8_t test_power_supply_voltage(void);
uint8_t test_gpio_outputs(void);
uint8_t test_all(i2c_handle_t *hi2c, spi_handle_t *hspi, test_result_t *result);

#endif
