#include "lsm6ds3.h"

static uint8_t lsm6ds3_write_reg(spi_handle_t *hspi, uint8_t reg, uint8_t data) {
    return spi_driver_write_reg(hspi, reg, data);
}

static uint8_t lsm6ds3_read_reg(spi_handle_t *hspi, uint8_t reg, uint8_t *data) {
    return spi_driver_read_reg(hspi, reg, data);
}

uint8_t lsm6ds3_init(lsm6ds3_handle_t *hlsm, spi_handle_t *hspi) {
    hlsm->hspi = hspi;
    uint8_t ret;

    ret = lsm6ds3_read_who_am_i(hlsm, &hlsm->who_am_i);
    if (ret != SPI_OK || hlsm->who_am_i != LSM6DS3_ID) {
        return 1;
    }

    ret = lsm6ds3_write_reg(hspi, LSM6DS3_CTRL3_C, 0x04); // Software reset
    if (ret != SPI_OK) return ret;

    hal_delay_ms(100);

    ret = lsm6ds3_configure_accel(hlsm, LSM6DS3_XL_RATE_119HZ, LSM6DS3_XL_RANGE_2G);
    if (ret != SPI_OK) return ret;

    ret = lsm6ds3_configure_gyro(hlsm, LSM6DS3_G_RATE_119HZ, LSM6DS3_G_RANGE_245DPS);
    if (ret != SPI_OK) return ret;

    return SPI_OK;
}

uint8_t lsm6ds3_read_who_am_i(lsm6ds3_handle_t *hlsm, uint8_t *id) {
    return lsm6ds3_read_reg(hlsm->hspi, LSM6DS3_WHO_AM_I, id);
}

uint8_t lsm6ds3_configure_accel(lsm6ds3_handle_t *hlsm, uint8_t rate, uint8_t range) {
    uint8_t ctrl1 = rate | range;
    return lsm6ds3_write_reg(hlsm->hspi, LSM6DS3_CTRL1_XL, ctrl1);
}

uint8_t lsm6ds3_configure_gyro(lsm6ds3_handle_t *hlsm, uint8_t rate, uint8_t range) {
    uint8_t ctrl2 = rate | range;
    return lsm6ds3_write_reg(hlsm->hspi, LSM6DS3_CTRL2_G, ctrl2);
}

uint8_t lsm6ds3_read_accel(lsm6ds3_handle_t *hlsm, lsm6ds3_axis_t *accel) {
    uint8_t buf[6];
    uint8_t ret;

    ret = spi_driver_read_burst(hlsm->hspi, LSM6DS3_OUTX_L_XL, buf, 6);
    if (ret != SPI_OK) return ret;

    accel->x = (int16_t)(buf[1] << 8 | buf[0]);
    accel->y = (int16_t)(buf[3] << 8 | buf[2]);
    accel->z = (int16_t)(buf[5] << 8 | buf[4]);

    return SPI_OK;
}

uint8_t lsm6ds3_read_gyro(lsm6ds3_handle_t *hlsm, lsm6ds3_axis_t *gyro) {
    uint8_t buf[6];
    uint8_t ret;

    ret = spi_driver_read_burst(hlsm->hspi, LSM6DS3_OUTX_L_G, buf, 6);
    if (ret != SPI_OK) return ret;

    gyro->x = (int16_t)(buf[1] << 8 | buf[0]);
    gyro->y = (int16_t)(buf[3] << 8 | buf[2]);
    gyro->z = (int16_t)(buf[5] << 8 | buf[4]);

    return SPI_OK;
}

uint8_t lsm6ds3_read_all(lsm6ds3_handle_t *hlsm, lsm6ds3_data_t *data) {
    uint8_t buf[12];
    uint8_t ret;

    ret = spi_driver_read_burst(hlsm->hspi, LSM6DS3_OUTX_L_G, buf, 12);
    if (ret != SPI_OK) return ret;

    data->gyro.x = (int16_t)(buf[1] << 8 | buf[0]);
    data->gyro.y = (int16_t)(buf[3] << 8 | buf[2]);
    data->gyro.z = (int16_t)(buf[5] << 8 | buf[4]);
    data->accel.x = (int16_t)(buf[7] << 8 | buf[6]);
    data->accel.y = (int16_t)(buf[9] << 8 | buf[8]);
    data->accel.z = (int16_t)(buf[11] << 8 | buf[10]);

    return SPI_OK;
}

float lsm6ds3_accel_to_mg(int16_t raw, uint8_t range) {
    float scale;
    switch (range) {
        case LSM6DS3_XL_RANGE_2G:  scale = 0.061f; break;
        case LSM6DS3_XL_RANGE_4G:  scale = 0.122f; break;
        case LSM6DS3_XL_RANGE_8G:  scale = 0.244f; break;
        case LSM6DS3_XL_RANGE_16G: scale = 0.488f; break;
        default: scale = 0.061f; break;
    }
    return (float)raw * scale;
}

float lsm6ds3_gyro_to_dps(int16_t raw, uint8_t range) {
    float scale;
    switch (range) {
        case LSM6DS3_G_RANGE_245DPS:  scale = 8.75f; break;
        case LSM6DS3_G_RANGE_500DPS:  scale = 17.50f; break;
        case LSM6DS3_G_RANGE_1000DPS: scale = 35.0f; break;
        case LSM6DS3_G_RANGE_2000DPS: scale = 70.0f; break;
        default: scale = 8.75f; break;
    }
    return (float)raw * scale;
}
