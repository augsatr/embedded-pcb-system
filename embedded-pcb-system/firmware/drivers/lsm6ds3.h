#ifndef LSM6DS3_H
#define LSM6DS3_H

#include "hal.h"
#include "spi_driver.h"

#define LSM6DS3_WHO_AM_I         0x0F
#define LSM6DS3_CTRL1_XL         0x10
#define LSM6DS3_CTRL2_G          0x11
#define LSM6DS3_CTRL3_C          0x12
#define LSM6DS3_CTRL4_C          0x13
#define LSM6DS3_CTRL5_C          0x14
#define LSM6DS3_CTRL6_C          0x15
#define LSM6DS3_CTRL7_G          0x16
#define LSM6DS3_CTRL8_XL         0x17
#define LSM6DS3_CTRL9_XL         0x18
#define LSM6DS3_CTRL10_C         0x19
#define LSM6DS3_INT1_CTRL        0x0D
#define LSM6DS3_INT2_CTRL        0x0E
#define LSM6DS3_STATUS_REG       0x1E
#define LSM6DS3_OUTX_L_G         0x22
#define LSM6DS3_OUTX_H_G         0x23
#define LSM6DS3_OUTY_L_G         0x24
#define LSM6DS3_OUTY_H_G         0x25
#define LSM6DS3_OUTZ_L_G         0x26
#define LSM6DS3_OUTZ_H_G         0x27
#define LSM6DS3_OUTX_L_XL        0x28
#define LSM6DS3_OUTX_H_XL        0x29
#define LSM6DS3_OUTY_L_XL        0x2A
#define LSM6DS3_OUTY_H_XL        0x2B
#define LSM6DS3_OUTZ_L_XL        0x2C
#define LSM6DS3_OUTZ_H_XL        0x2D

#define LSM6DS3_ID               0x69

#define LSM6DS3_XL_RATE_10HZ     0x10
#define LSM6DS3_XL_RATE_50HZ     0x20
#define LSM6DS3_XL_RATE_119HZ    0x30
#define LSM6DS3_XL_RATE_238HZ    0x40
#define LSM6DS3_XL_RATE_476HZ    0x50
#define LSM6DS3_XL_RATE_952HZ    0x60

#define LSM6DS3_G_RATE_15HZ      0x10
#define LSM6DS3_G_RATE_60HZ      0x20
#define LSM6DS3_G_RATE_119HZ     0x30
#define LSM6DS3_G_RATE_238HZ     0x40
#define LSM6DS3_G_RATE_476HZ     0x50
#define LSM6DS3_G_RATE_952HZ     0x60

#define LSM6DS3_XL_RANGE_2G      0x00
#define LSM6DS3_XL_RANGE_4G      0x08
#define LSM6DS3_XL_RANGE_8G      0x10
#define LSM6DS3_XL_RANGE_16G     0x18

#define LSM6DS3_G_RANGE_245DPS   0x00
#define LSM6DS3_G_RANGE_500DPS   0x04
#define LSM6DS3_G_RANGE_1000DPS  0x08
#define LSM6DS3_G_RANGE_2000DPS  0x0C

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} lsm6ds3_axis_t;

typedef struct {
    lsm6ds3_axis_t accel;
    lsm6ds3_axis_t gyro;
} lsm6ds3_data_t;

typedef struct {
    spi_handle_t *hspi;
    uint8_t who_am_i;
} lsm6ds3_handle_t;

uint8_t lsm6ds3_init(lsm6ds3_handle_t *hlsm, spi_handle_t *hspi);
uint8_t lsm6ds3_read_who_am_i(lsm6ds3_handle_t *hlsm, uint8_t *id);
uint8_t lsm6ds3_configure_accel(lsm6ds3_handle_t *hlsm, uint8_t rate, uint8_t range);
uint8_t lsm6ds3_configure_gyro(lsm6ds3_handle_t *hlsm, uint8_t rate, uint8_t range);
uint8_t lsm6ds3_read_accel(lsm6ds3_handle_t *hlsm, lsm6ds3_axis_t *accel);
uint8_t lsm6ds3_read_gyro(lsm6ds3_handle_t *hlsm, lsm6ds3_axis_t *gyro);
uint8_t lsm6ds3_read_all(lsm6ds3_handle_t *hlsm, lsm6ds3_data_t *data);
float lsm6ds3_accel_to_mg(int16_t raw, uint8_t range);
float lsm6ds3_gyro_to_dps(int16_t raw, uint8_t range);

#endif
