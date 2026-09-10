#ifndef BME280_H
#define BME280_H

#include "hal.h"
#include "i2c_driver.h"

#define BME280_I2C_ADDR_0  0x76
#define BME280_I2C_ADDR_1  0x77

#define BME280_REG_ID          0xD0
#define BME280_REG_RESET       0xE0
#define BME280_REG_CTRL_HUM    0xF2
#define BME280_REG_CTRL_MEAS   0xF4
#define BME280_REG_CONFIG      0xF5
#define BME280_REG_PRESS_MSB   0xF7
#define BME280_REG_TEMP_MSB    0xFA
#define BME280_REG_HUM_MSB     0xFD

#define BME280_CHIP_ID  0x60
#define BME280_RESET    0xB6

#define BME280_MODE_NORMAL  0x03
#define BME280_MODE_FORCED  0x01
#define BME280_MODE_SLEEP   0x00

#define BME280_OVERSAMPLING_1   0x01
#define BME280_OVERSAMPLING_2   0x02
#define BME280_OVERSAMPLING_4   0x03
#define BME280_OVERSAMPLING_8   0x04
#define BME280_OVERSAMPLING_16  0x05

typedef struct {
    int32_t temperature;
    uint32_t pressure;
    uint32_t humidity;
} bme280_data_t;

typedef struct {
    i2c_handle_t *hi2c;
    uint8_t dev_addr;
    int32_t t_fine;
    int32_t dig_T1, dig_T2, dig_T3;
    int32_t dig_P1;
    int32_t dig_P2, dig_P3, dig_P4, dig_P5;
    int32_t dig_P6, dig_P7, dig_P8, dig_P9;
    int32_t dig_H1, dig_H2, dig_H3, dig_H4, dig_H5, dig_H6;
} bme280_handle_t;

uint8_t bme280_init(bme280_handle_t *hbme, i2c_handle_t *hi2c, uint8_t addr);
uint8_t bme280_read_id(bme280_handle_t *hbme, uint8_t *id);
uint8_t bme280_configure(bme280_handle_t *hbme, uint8_t osrs_t, uint8_t osrs_p, uint8_t osrs_h, uint8_t mode);
uint8_t bme280_read_raw(bme280_handle_t *hbme, bme280_data_t *data);
uint8_t bme280_compensate(bme280_handle_t *hbme, bme280_data_t *raw, bme280_data_t *comp);
uint8_t bme280_read_temperature(bme280_handle_t *hbme, float *temp_c);
uint8_t bme280_read_pressure(bme280_handle_t *hbme, float *pres_pa);
uint8_t bme280_read_humidity(bme280_handle_t *hbme, float *hum_pct);

#endif
