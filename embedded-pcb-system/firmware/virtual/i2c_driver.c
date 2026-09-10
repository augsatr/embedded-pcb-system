#include "i2c_driver.h"

static uint8_t i2c_sim_regs[128] = {0};
static uint8_t i2c_sim_device_found = 1;

uint8_t i2c_driver_init(i2c_handle_t *hi2c, I2C_TypeDef *instance, uint32_t clock_speed) {
    hi2c->instance = instance;
    hi2c->timeout = 10000;
    printf("[I2C] Driver initialized at %d Hz\n", clock_speed);
    return I2C_OK;
}

uint8_t i2c_driver_write_reg(i2c_handle_t *hi2c, uint8_t reg, uint8_t data) {
    i2c_sim_regs[reg & 0x7F] = data;
    printf("[I2C] Write reg 0x%02X = 0x%02X\n", reg, data);
    return I2C_OK;
}

uint8_t i2c_driver_read_reg(i2c_handle_t *hi2c, uint8_t reg, uint8_t *data) {
    *data = i2c_sim_regs[reg & 0x7F];
    printf("[I2C] Read reg 0x%02X = 0x%02X\n", reg, *data);
    return I2C_OK;
}

uint8_t i2c_driver_write_burst(i2c_handle_t *hi2c, uint8_t reg, uint8_t *data, uint16_t len) {
    uint16_t i;
    for (i = 0; i < len; i++) {
        i2c_sim_regs[(reg + i) & 0x7F] = data[i];
    }
    printf("[I2C] Burst write reg 0x%02X, %d bytes\n", reg, len);
    return I2C_OK;
}

uint8_t i2c_driver_read_burst(i2c_handle_t *hi2c, uint8_t reg, uint8_t *data, uint16_t len) {
    uint16_t i;
    for (i = 0; i < len; i++) {
        data[i] = i2c_sim_regs[(reg + i) & 0x7F];
    }
    printf("[I2C] Burst read reg 0x%02X, %d bytes\n", reg, len);
    return I2C_OK;
}

uint8_t i2c_driver_scan_bus(I2C_TypeDef *i2c, uint8_t *found_addrs, uint8_t *count) {
    printf("[I2C] Scanning bus...\n");

    *count = 0;

    found_addrs[*count] = 0x76;
    (*count)++;
    printf("[I2C] Found device at 0x%02X (BME280)\n", 0x76);

    found_addrs[*count] = 0x68;
    (*count)++;
    printf("[I2C] Found device at 0x%02X (LSM6DS3 alt)\n", 0x68);

    printf("[I2C] Scan complete: %d devices found\n", *count);
    return I2C_OK;
}

void i2c_simulate_bme280(void) {
    i2c_sim_regs[0xD0] = 0x60; // Chip ID

    i2c_sim_regs[0x88] = 0x71; // dig_T1 LSB
    i2c_sim_regs[0x89] = 0x6C; // dig_T1 MSB
    i2c_sim_regs[0x8A] = 0x68; // dig_T2 LSB
    i2c_sim_regs[0x8B] = 0x32; // dig_T2 MSB
    i2c_sim_regs[0x8C] = 0xD0; // dig_T3 LSB
    i2c_sim_regs[0x8D] = 0x0B; // dig_T3 MSB

    float temp_c = 25.0f + (rand() % 100) / 10.0f;
    int32_t raw_temp = (int32_t)((temp_c - 25.0f) * 65536.0f / 51.2f);
    i2c_sim_regs[0xFA] = (raw_temp >> 12) & 0xFF;
    i2c_sim_regs[0xFB] = (raw_temp >> 4) & 0xFF;
    i2c_sim_regs[0xFC] = (raw_temp << 4) & 0xF0;

    uint32_t raw_press = 10132500;
    i2c_sim_regs[0xF7] = (raw_press >> 12) & 0xFF;
    i2c_sim_regs[0xF8] = (raw_press >> 4) & 0xFF;
    i2c_sim_regs[0xF9] = (raw_press << 4) & 0xF0;

    uint16_t raw_hum = 45000;
    i2c_sim_regs[0xFD] = (raw_hum >> 8) & 0xFF;
    i2c_sim_regs[0xFE] = raw_hum & 0xFF;

    printf("[SIM] BME280 simulated: T=%.1fC P=%dPa H=%d%%\n",
           temp_c, raw_press / 100, raw_hum / 1000);
}
