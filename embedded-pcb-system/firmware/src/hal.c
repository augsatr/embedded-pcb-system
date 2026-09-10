#include "hal.h"

static volatile uint32_t systick_ms = 0;

void SysTick_Handler(void) {
    systick_ms++;
}

void hal_init(void) {
    RCC_CR |= (1 << 16); // HSE ON
    while (!(RCC_CR & (1 << 17))); // Wait HSE ready

    RCC_CFGR |= (0x07 << 18); // PLL multiplier 9
    RCC_CFGR |= (1 << 16);    // PLL source HSE
    RCC_CFGR |= (0x00 << 11); // APB1 = HCLK/2

    FLASH_BASE->ACR |= (0x02); // Flash latency 2 wait states

    RCC_CR |= (1 << 24); // PLL ON
    while (!(RCC_CR & (1 << 25))); // Wait PLL ready

    RCC_CFGR |= (0x02); // Switch to PLL
    while ((RCC_CFGR & (0x0C)) != (0x02 << 2)); // Wait switch

    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC_APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

    // SysTick: 72MHz / 1000 = 72000
    SYSTICK->LOAD = 72000 - 1;
    SYSTICK->VAL = 0;
    SYSTICK->CR = 0x07; // ENABLE, TICKINT, CLKSOURCE
}

void hal_delay_ms(uint32_t ms) {
    uint32_t start = systick_ms;
    while ((systick_ms - start) < ms);
}

void hal_delay_us(uint32_t us) {
    uint32_t i;
    for (i = 0; i < us * 8; i++) {
        __asm volatile("nop");
    }
}

uint32_t hal_get_tick(void) {
    return systick_ms;
}

void hal_gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode) {
    volatile uint32_t *cr;
    uint8_t shift;

    if (pin < 8) {
        cr = &GPIO_CRL(port);
        shift = pin * 4;
    } else {
        cr = &GPIO_CRH(port);
        shift = (pin - 8) * 4;
    }

    *cr = (*cr & ~(0xF << shift)) | ((mode & 0xF) << shift);
}

void hal_gpio_write(GPIO_TypeDef *port, uint8_t pin, bool state) {
    if (state) {
        GPIO_BSRR(port) = (1 << pin);
    } else {
        GPIO_BSRR(port) = (1 << (pin + 16));
    }
}

bool hal_gpio_read(GPIO_TypeDef *port, uint8_t pin) {
    return (GPIO_IDR(port) & (1 << pin)) != 0;
}

uint8_t hal_i2c_init(I2C_TypeDef *i2c, uint32_t clock_speed) {
    i2c->CR2 = 36;
    i2c->CCR = (36000000 / (2 * clock_speed)) & 0xFFF;
    i2c->TRISE = 36000000 / 1000000 + 1;
    i2c->CR1 |= (1 << 0);
    return HAL_OK;
}

uint8_t hal_i2c_start(I2C_TypeDef *i2c) {
    i2c->CR1 |= (1 << 8);
    uint32_t timeout = 100000;
    while (!(i2c->SR1 & (1 << 10))) {
        if (--timeout == 0) return HAL_TIMEOUT;
    }
    return HAL_OK;
}

uint8_t hal_i2c_stop(I2C_TypeDef *i2c) {
    i2c->CR1 |= (1 << 9);
    return HAL_OK;
}

uint8_t hal_i2c_send_address(I2C_TypeDef *i2c, uint8_t address, bool rw) {
    i2c->DR = (address << 1) | (rw ? 1 : 0);
    uint32_t timeout = 100000;
    while (!(i2c->SR1 & (1 << 10))) {
        if (--timeout == 0) return HAL_TIMEOUT;
    }
    (void)i2c->SR2;
    return HAL_OK;
}

uint8_t hal_i2c_send_data(I2C_TypeDef *i2c, uint8_t data) {
    uint32_t timeout = 100000;
    while (!(i2c->SR1 & (1 << 7))) {
        if (--timeout == 0) return HAL_TIMEOUT;
    }
    i2c->DR = data;
    return HAL_OK;
}

uint8_t hal_i2c_receive_data(I2C_TypeDef *i2c, uint8_t *data, bool ack) {
    if (!ack) {
        i2c->CR1 &= ~(1 << 10);
    }
    uint32_t timeout = 100000;
    while (!(i2c->SR1 & (1 << 6))) {
        if (--timeout == 0) return HAL_TIMEOUT;
    }
    *data = i2c->DR;
    return HAL_OK;
}

uint8_t hal_i2c_write_reg(I2C_TypeDef *i2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t data) {
    uint8_t result;
    result = hal_i2c_start(i2c);
    if (result != HAL_OK) return result;
    result = hal_i2c_send_address(i2c, dev_addr, false);
    if (result != HAL_OK) return result;
    result = hal_i2c_send_data(i2c, reg_addr);
    if (result != HAL_OK) return result;
    result = hal_i2c_send_data(i2c, data);
    if (result != HAL_OK) return result;
    hal_i2c_stop(i2c);
    return HAL_OK;
}

uint8_t hal_i2c_read_reg(I2C_TypeDef *i2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data) {
    uint8_t result;
    result = hal_i2c_start(i2c);
    if (result != HAL_OK) return result;
    result = hal_i2c_send_address(i2c, dev_addr, false);
    if (result != HAL_OK) return result;
    result = hal_i2c_send_data(i2c, reg_addr);
    if (result != HAL_OK) return result;
    result = hal_i2c_start(i2c);
    if (result != HAL_OK) return result;
    result = hal_i2c_send_address(i2c, dev_addr, true);
    if (result != HAL_OK) return result;
    result = hal_i2c_receive_data(i2c, data, false);
    if (result != HAL_OK) return result;
    hal_i2c_stop(i2c);
    return HAL_OK;
}

uint8_t hal_i2c_read_burst(I2C_TypeDef *i2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
    uint8_t result;
    uint16_t i;
    result = hal_i2c_start(i2c);
    if (result != HAL_OK) return result;
    result = hal_i2c_send_address(i2c, dev_addr, false);
    if (result != HAL_OK) return result;
    result = hal_i2c_send_data(i2c, reg_addr);
    if (result != HAL_OK) return result;
    result = hal_i2c_start(i2c);
    if (result != HAL_OK) return result;
    result = hal_i2c_send_address(i2c, dev_addr, true);
    if (result != HAL_OK) return result;
    for (i = 0; i < len; i++) {
        result = hal_i2c_receive_data(i2c, &data[i], (i < len - 1));
        if (result != HAL_OK) return result;
    }
    hal_i2c_stop(i2c);
    return HAL_OK;
}

uint8_t hal_spi_init(SPI_TypeDef *spi, uint8_t prescaler) {
    spi->CR1 = 0;
    spi->CR1 |= (1 << 6);       // SPE
    spi->CR1 |= (1 << 2);       // MSTR
    spi->CR1 |= (prescaler & 0x07) << 3;
    return HAL_OK;
}

uint8_t hal_spi_transfer(SPI_TypeDef *spi, uint8_t data) {
    uint32_t timeout = 100000;
    while (!(spi->SR & (1 << 1))) {
        if (--timeout == 0) return HAL_TIMEOUT;
    }
    spi->DR = data;
    timeout = 100000;
    while (!(spi->SR & (1 << 0))) {
        if (--timeout == 0) return HAL_TIMEOUT;
    }
    return spi->DR;
}

uint8_t hal_spi_transfer_byte(SPI_TypeDef *spi, uint8_t data) {
    return hal_spi_transfer(spi, data);
}

void hal_spi_cs_low(GPIO_TypeDef *port, uint8_t pin) {
    GPIO_BSRR(port) = (1 << (pin + 16));
}

void hal_spi_cs_high(GPIO_TypeDef *port, uint8_t pin) {
    GPIO_BSRR(port) = (1 << pin);
}
