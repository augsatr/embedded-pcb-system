#include "spi_driver.h"

static uint8_t spi_wait_tx_empty(SPI_TypeDef *spi, uint32_t timeout) {
    uint32_t tick = 0;
    while (!(spi->SR & (1 << 1))) {
        if (++tick > timeout) return SPI_ERR_TIMEOUT;
    }
    return SPI_OK;
}

static uint8_t spi_wait_rx_not_empty(SPI_TypeDef *spi, uint32_t timeout) {
    uint32_t tick = 0;
    while (!(spi->SR & (1 << 0))) {
        if (++tick > timeout) return SPI_ERR_TIMEOUT;
    }
    return SPI_OK;
}

static uint8_t spi_wait_busy(SPI_TypeDef *spi, uint32_t timeout) {
    uint32_t tick = 0;
    while (spi->SR & (1 << 7)) {
        if (++tick > timeout) return SPI_ERR_TIMEOUT;
    }
    return SPI_OK;
}

uint8_t spi_driver_init(spi_handle_t *hspi, SPI_TypeDef *instance, uint8_t mode, uint8_t prescaler) {
    hspi->instance = instance;
    hspi->mode = mode;
    hspi->prescaler = prescaler;

    uint16_t cr1 = 0;
    cr1 |= (1 << 6);       // SPE
    cr1 |= (1 << 2);       // MSTR
    cr1 |= (prescaler & 0x07) << 3;

    switch (mode) {
        case SPI_MODE0:
            cr1 &= ~(1 << 1); // CPOL = 0
            cr1 &= ~(1 << 0); // CPHA = 0
            break;
        case SPI_MODE1:
            cr1 &= ~(1 << 1); // CPOL = 0
            cr1 |= (1 << 0);  // CPHA = 1
            break;
        case SPI_MODE2:
            cr1 |= (1 << 1);  // CPOL = 1
            cr1 &= ~(1 << 0); // CPHA = 0
            break;
        case SPI_MODE3:
            cr1 |= (1 << 1);  // CPOL = 1
            cr1 |= (1 << 0);  // CPHA = 1
            break;
    }

    instance->CR1 = cr1;
    return SPI_OK;
}

uint8_t spi_driver_transfer(spi_handle_t *hspi, uint8_t tx, uint8_t *rx) {
    SPI_TypeDef *spi = hspi->instance;
    uint8_t result;

    result = spi_wait_tx_empty(spi, 10000);
    if (result != SPI_OK) return result;

    spi->DR = tx;
    result = spi_wait_rx_not_empty(spi, 10000);
    if (result != SPI_OK) return result;

    *rx = spi->DR;
    result = spi_wait_busy(spi, 10000);
    return result;
}

uint8_t spi_driver_transfer_burst(spi_handle_t *hspi, uint8_t *tx, uint8_t *rx, uint16_t len) {
    SPI_TypeDef *spi = hspi->instance;
    uint8_t result;
    uint16_t i;

    for (i = 0; i < len; i++) {
        result = spi_wait_tx_empty(spi, 10000);
        if (result != SPI_OK) return result;

        spi->DR = tx[i];
        result = spi_wait_rx_not_empty(spi, 10000);
        if (result != SPI_OK) return result;

        rx[i] = spi->DR;
    }

    result = spi_wait_busy(spi, 10000);
    return result;
}

uint8_t spi_driver_write_reg(spi_handle_t *hspi, uint8_t reg, uint8_t data) {
    uint8_t rx;
    uint8_t result;

    hal_spi_cs_low(hspi->cs_port, hspi->cs_pin);
    result = spi_driver_transfer(hspi, reg & 0x7F, &rx);
    if (result != SPI_OK) {
        hal_spi_cs_high(hspi->cs_port, hspi->cs_pin);
        return result;
    }
    result = spi_driver_transfer(hspi, data, &rx);
    hal_spi_cs_high(hspi->cs_port, hspi->cs_pin);
    return result;
}

uint8_t spi_driver_read_reg(spi_handle_t *hspi, uint8_t reg, uint8_t *data) {
    uint8_t rx;
    uint8_t result;

    hal_spi_cs_low(hspi->cs_port, hspi->cs_pin);
    result = spi_driver_transfer(hspi, reg | 0x80, &rx);
    if (result != SPI_OK) {
        hal_spi_cs_high(hspi->cs_port, hspi->cs_pin);
        return result;
    }
    result = spi_driver_transfer(hspi, 0x00, data);
    hal_spi_cs_high(hspi->cs_port, hspi->cs_pin);
    return result;
}

uint8_t spi_driver_read_burst(spi_handle_t *hspi, uint8_t reg, uint8_t *data, uint16_t len) {
    uint8_t result;
    uint16_t i;

    hal_spi_cs_low(hspi->cs_port, hspi->cs_pin);

    uint8_t dummy;
    result = spi_driver_transfer(hspi, reg | 0x80, &dummy);
    if (result != SPI_OK) {
        hal_spi_cs_high(hspi->cs_port, hspi->cs_pin);
        return result;
    }

    for (i = 0; i < len; i++) {
        result = spi_driver_transfer(hspi, 0x00, &data[i]);
        if (result != SPI_OK) {
            hal_spi_cs_high(hspi->cs_port, hspi->cs_pin);
            return result;
        }
    }

    hal_spi_cs_high(hspi->cs_port, hspi->cs_pin);
    return SPI_OK;
}
