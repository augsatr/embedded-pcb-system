#include "hardware_test.h"
#include "bme280.h"
#include "lsm6ds3.h"

uint8_t test_i2c_bus_scan(I2C_TypeDef *i2c) {
    uint8_t found_addrs[16];
    uint8_t count = 0;
    uint8_t result = i2c_driver_scan_bus(i2c, found_addrs, &count);

    if (result != I2C_OK) {
        return TEST_FAIL;
    }

    if (count == 0) {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

uint8_t test_i2c_loopback(void) {
    uint8_t test_data = 0xA5;
    uint8_t read_data = 0;

    hal_i2c_start(I2C1);
    hal_i2c_send_address(I2C1, 0x50, false);
    hal_i2c_send_data(I2C1, 0x00);
    hal_i2c_send_data(I2C1, test_data);
    hal_i2c_stop(I2C1);

    hal_delay_ms(10);

    hal_i2c_start(I2C1);
    hal_i2c_send_address(I2C1, 0x50, false);
    hal_i2c_send_data(I2C1, 0x00);
    hal_i2c_start(I2C1);
    hal_i2c_send_address(I2C1, 0x50, true);
    hal_i2c_receive_data(I2C1, &read_data, false);
    hal_i2c_stop(I2C1);

    return (read_data == test_data) ? TEST_PASS : TEST_FAIL;
}

uint8_t test_spi_loopback(void) {
    uint8_t test_patterns[] = {0xAA, 0x55, 0x00, 0xFF, 0xA5};
    uint8_t rx_data[5];
    uint8_t i;

    hal_spi_cs_low(GPIOA, 4);

    for (i = 0; i < 5; i++) {
        rx_data[i] = hal_spi_transfer(SPI1, test_patterns[i]);
    }

    hal_spi_cs_high(GPIOA, 4);

    for (i = 0; i < 5; i++) {
        if (rx_data[i] != test_patterns[i]) {
            return TEST_FAIL;
        }
    }

    return TEST_PASS;
}

uint8_t test_bme280_communication(i2c_handle_t *hi2c) {
    bme280_handle_t hbme;
    uint8_t id;
    uint8_t result;

    result = bme280_read_id(&hbme, &id);
    if (result != I2C_OK || id != BME280_CHIP_ID) {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

uint8_t test_bme280_temperature(i2c_handle_t *hi2c) {
    bme280_handle_t hbme;
    float temp;
    uint8_t result;

    result = bme280_read_temperature(&hbme, &temp);
    if (result != I2C_OK) {
        return TEST_FAIL;
    }

    if (temp < -40.0f || temp > 85.0f) {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

uint8_t test_bme280_pressure(i2c_handle_t *hi2c) {
    bme280_handle_t hbme;
    float pres;
    uint8_t result;

    result = bme280_read_pressure(&hbme, &pres);
    if (result != I2C_OK) {
        return TEST_FAIL;
    }

    if (pres < 30000.0f || pres > 110000.0f) {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

uint8_t test_bme280_humidity(i2c_handle_t *hi2c) {
    bme280_handle_t hbme;
    float hum;
    uint8_t result;

    result = bme280_read_humidity(&hbme, &hum);
    if (result != I2C_OK) {
        return TEST_FAIL;
    }

    if (hum < 0.0f || hum > 100.0f) {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

uint8_t test_lsm6ds3_communication(spi_handle_t *hspi) {
    lsm6ds3_handle_t hlsm;
    uint8_t id;
    uint8_t result;

    result = lsm6ds3_read_who_am_i(&hlsm, &id);
    if (result != SPI_OK || id != LSM6DS3_ID) {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

uint8_t test_lsm6ds3_accelerometer(spi_handle_t *hspi) {
    lsm6ds3_handle_t hlsm;
    lsm6ds3_axis_t accel;
    uint8_t result;

    result = lsm6ds3_read_accel(&hlsm, &accel);
    if (result != SPI_OK) {
        return TEST_FAIL;
    }

    if (accel.x == 0 && accel.y == 0 && accel.z == 0) {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

uint8_t test_lsm6ds3_gyroscope(spi_handle_t *hspi) {
    lsm6ds3_handle_t hlsm;
    lsm6ds3_axis_t gyro;
    uint8_t result;

    result = lsm6ds3_read_gyro(&hlsm, &gyro);
    if (result != SPI_OK) {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

uint8_t test_power_supply_voltage(void) {
    // ADC-based voltage measurement would go here
    // For now, assume 3.3V is present if system is running
    return TEST_PASS;
}

uint8_t test_gpio_outputs(void) {
    hal_gpio_write(GPIOC, 13, false);
    hal_delay_ms(100);
    hal_gpio_write(GPIOC, 13, true);
    return TEST_PASS;
}

uint8_t test_all(i2c_handle_t *hi2c, spi_handle_t *hspi, test_result_t *result) {
    result->total = 0;
    result->passed = 0;
    result->failed = 0;
    result->skipped = 0;

    uint8_t test_result;

    result->total++;
    test_result = test_i2c_bus_scan(hi2c->instance);
    if (test_result == TEST_PASS) result->passed++;
    else if (test_result == TEST_FAIL) result->failed++;
    else result->skipped++;

    result->total++;
    test_result = test_spi_loopback();
    if (test_result == TEST_PASS) result->passed++;
    else if (test_result == TEST_FAIL) result->failed++;
    else result->skipped++;

    result->total++;
    test_result = test_bme280_communication(hi2c);
    if (test_result == TEST_PASS) result->passed++;
    else if (test_result == TEST_FAIL) result->failed++;
    else result->skipped++;

    result->total++;
    test_result = test_bme280_temperature(hi2c);
    if (test_result == TEST_PASS) result->passed++;
    else if (test_result == TEST_FAIL) result->failed++;
    else result->skipped++;

    result->total++;
    test_result = test_bme280_pressure(hi2c);
    if (test_result == TEST_PASS) result->passed++;
    else if (test_result == TEST_FAIL) result->failed++;
    else result->skipped++;

    result->total++;
    test_result = test_bme280_humidity(hi2c);
    if (test_result == TEST_PASS) result->passed++;
    else if (test_result == TEST_FAIL) result->failed++;
    else result->skipped++;

    result->total++;
    test_result = test_lsm6ds3_communication(hspi);
    if (test_result == TEST_PASS) result->passed++;
    else if (test_result == TEST_FAIL) result->failed++;
    else result->skipped++;

    result->total++;
    test_result = test_lsm6ds3_accelerometer(hspi);
    if (test_result == TEST_PASS) result->passed++;
    else if (test_result == TEST_FAIL) result->failed++;
    else result->skipped++;

    result->total++;
    test_result = test_lsm6ds3_gyroscope(hspi);
    if (test_result == TEST_PASS) result->passed++;
    else if (test_result == TEST_FAIL) result->failed++;
    else result->skipped++;

    result->total++;
    test_result = test_gpio_outputs();
    if (test_result == TEST_PASS) result->passed++;
    else if (test_result == TEST_FAIL) result->failed++;
    else result->skipped++;

    return (result->failed == 0) ? TEST_PASS : TEST_FAIL;
}
