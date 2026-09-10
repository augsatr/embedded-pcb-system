#include "spi_driver.h"

static uint8_t spi_sim_regs[256] = {0};

uint8_t spi_driver_init(spi_handle_t *hspi, SPI_TypeDef *instance, uint8_t mode, uint8_t prescaler) {
    hspi->instance = instance;
    hspi->mode = mode;
    hspi->prescaler = prescaler;
    printf("[SPI] Driver initialized: mode=%d, prescaler=%d\n", mode, prescaler);
    return SPI_OK;
}

uint8_t spi_driver_transfer(spi_handle_t *hspi, uint8_t tx, uint8_t *rx) {
    uint8_t reg_addr = tx & 0x7F;
    uint8_t is_read = (tx & 0x80) != 0;

    if (is_read) {
        *rx = spi_sim_regs[reg_addr];
        printf("[SPI] Transfer: TX=0x%02X (read reg 0x%02X), RX=0x%02X\n",
               tx, reg_addr, *rx);
    } else {
        spi_sim_regs[reg_addr] = 0xFF;
        *rx = 0xFF;
        printf("[SPI] Transfer: TX=0x%02X (write reg 0x%02X), RX=0x%02X\n",
               tx, reg_addr, *rx);
    }
    return SPI_OK;
}

uint8_t spi_driver_transfer_burst(spi_handle_t *hspi, uint8_t *tx, uint8_t *rx, uint16_t len) {
    uint16_t i;
    for (i = 0; i < len; i++) {
        uint8_t result = spi_driver_transfer(hspi, tx[i], &rx[i]);
        if (result != SPI_OK) return result;
    }
    printf("[SPI] Burst transfer: %d bytes\n", len);
    return SPI_OK;
}

uint8_t spi_driver_write_reg(spi_handle_t *hspi, uint8_t reg, uint8_t data) {
    uint8_t rx;
    hal_spi_cs_low(hspi->cs_port, hspi->cs_pin);
    spi_driver_transfer(hspi, reg & 0x7F, &rx);
    spi_driver_transfer(hspi, data, &rx);
    hal_spi_cs_high(hspi->cs_port, hspi->cs_pin);
    printf("[SPI] Write reg 0x%02X = 0x%02X\n", reg, data);
    return SPI_OK;
}

uint8_t spi_driver_read_reg(spi_handle_t *hspi, uint8_t reg, uint8_t *data) {
    uint8_t rx;
    hal_spi_cs_low(hspi->cs_port, hspi->cs_pin);
    spi_driver_transfer(hspi, reg | 0x80, &rx);
    spi_driver_transfer(hspi, 0x00, data);
    hal_spi_cs_high(hspi->cs_port, hspi->cs_pin);
    printf("[SPI] Read reg 0x%02X = 0x%02X\n", reg, *data);
    return SPI_OK;
}

uint8_t spi_driver_read_burst(spi_handle_t *hspi, uint8_t reg, uint8_t *data, uint16_t len) {
    uint8_t dummy;
    uint16_t i;

    hal_spi_cs_low(hspi->cs_port, hspi->cs_pin);
    spi_driver_transfer(hspi, reg | 0x80, &dummy);

    for (i = 0; i < len; i++) {
        spi_driver_transfer(hspi, 0x00, &data[i]);
    }

    hal_spi_cs_high(hspi->cs_port, hspi->cs_pin);
    printf("[SPI] Burst read reg 0x%02X, %d bytes\n", reg, len);
    return SPI_OK;
}

void spi_simulate_lsm6ds3(void) {
    spi_sim_regs[0x0F] = 0x69; // WHO_AM_I

    int16_t accel_x = 204;
    int16_t accel_y = -102;
    int16_t accel_z = 16384;
    spi_sim_regs[0x28] = accel_x & 0xFF;
    spi_sim_regs[0x29] = (accel_x >> 8) & 0xFF;
    spi_sim_regs[0x2A] = accel_y & 0xFF;
    spi_sim_regs[0x2B] = (accel_y >> 8) & 0xFF;
    spi_sim_regs[0x2C] = accel_z & 0xFF;
    spi_sim_regs[0x2D] = (accel_z >> 8) & 0xFF;

    int16_t gyro_x = 128;
    int16_t gyro_y = -64;
    int16_t gyro_z = 32;
    spi_sim_regs[0x22] = gyro_x & 0xFF;
    spi_sim_regs[0x23] = (gyro_x >> 8) & 0xFF;
    spi_sim_regs[0x24] = gyro_y & 0xFF;
    spi_sim_regs[0x25] = (gyro_y >> 8) & 0xFF;
    spi_sim_regs[0x26] = gyro_z & 0xFF;
    spi_sim_regs[0x27] = (gyro_z >> 8) & 0xFF;

    printf("[SIM] LSM6DS3 simulated: Accel=%d,%d,%d Gyro=%d,%d,%d\n",
           accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z);
}
