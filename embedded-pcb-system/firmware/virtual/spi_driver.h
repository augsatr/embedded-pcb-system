#ifndef VIRTUAL_SPI_DRIVER_H
#define VIRTUAL_SPI_DRIVER_H

#include "virtual_hal.h"

#define SPI_MODE0  0x00
#define SPI_MODE1  0x01
#define SPI_MODE2  0x02
#define SPI_MODE3  0x03

#define SPI_SPEED_DIV2    0x00
#define SPI_SPEED_DIV4    0x01
#define SPI_SPEED_DIV8    0x02
#define SPI_SPEED_DIV16   0x03
#define SPI_SPEED_DIV32   0x04
#define SPI_SPEED_DIV64   0x05
#define SPI_SPEED_DIV128  0x06

#define SPI_OK       0
#define SPI_ERR      1
#define SPI_ERR_TIMEOUT 2

typedef struct {
    SPI_TypeDef *instance;
    GPIO_TypeDef *cs_port;
    uint8_t cs_pin;
    uint8_t mode;
    uint8_t prescaler;
} spi_handle_t;

uint8_t spi_driver_init(spi_handle_t *hspi, SPI_TypeDef *instance, uint8_t mode, uint8_t prescaler);
uint8_t spi_driver_transfer(spi_handle_t *hspi, uint8_t tx, uint8_t *rx);
uint8_t spi_driver_transfer_burst(spi_handle_t *hspi, uint8_t *tx, uint8_t *rx, uint16_t len);
uint8_t spi_driver_write_reg(spi_handle_t *hspi, uint8_t reg, uint8_t data);
uint8_t spi_driver_read_reg(spi_handle_t *hspi, uint8_t reg, uint8_t *data);
uint8_t spi_driver_read_burst(spi_handle_t *hspi, uint8_t reg, uint8_t *data, uint16_t len);

#endif
