#include "i2c_driver.h"

static uint8_t i2c_wait_flag(I2C_TypeDef *i2c, uint32_t flag, uint32_t timeout) {
    uint32_t tick = 0;
    while (!(i2c->SR1 & flag)) {
        if (++tick > timeout) return I2C_ERR_TIMEOUT;
    }
    return I2C_OK;
}

uint8_t i2c_driver_init(i2c_handle_t *hi2c, I2C_TypeDef *instance, uint32_t clock_speed) {
    hi2c->instance = instance;
    hi2c->timeout = 10000;

    instance->CR2 = 36; // APB1 clock = 36MHz
    instance->CCR = (36000000 / (2 * clock_speed)) & 0xFFF;
    instance->TRISE = 36000000 / 1000000 + 1;
    instance->CR1 |= (1 << 0); // Enable I2C

    return I2C_OK;
}

uint8_t i2c_driver_write_reg(i2c_handle_t *hi2c, uint8_t reg, uint8_t data) {
    I2C_TypeDef *i2c = hi2c->instance;
    uint8_t result;

    i2c->CR1 |= (1 << 8); // START
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout); // SB
    if (result != I2C_OK) return result;

    i2c->DR = (hi2c->dev_addr << 1) | I2C_WRITE;
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout); // ADDR
    if (result != I2C_OK) return result;
    (void)i2c->SR2; // Clear ADDR

    i2c->DR = reg;
    result = i2c_wait_flag(i2c, (1 << 7), hi2c->timeout); // TXE
    if (result != I2C_OK) return result;

    i2c->DR = data;
    result = i2c_wait_flag(i2c, (1 << 7), hi2c->timeout); // TXE
    if (result != I2C_OK) return result;

    i2c->CR1 |= (1 << 9); // STOP
    return I2C_OK;
}

uint8_t i2c_driver_read_reg(i2c_handle_t *hi2c, uint8_t reg, uint8_t *data) {
    I2C_TypeDef *i2c = hi2c->instance;
    uint8_t result;

    i2c->CR1 |= (1 << 8); // START
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout);
    if (result != I2C_OK) return result;

    i2c->DR = (hi2c->dev_addr << 1) | I2C_WRITE;
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout);
    if (result != I2C_OK) return result;
    (void)i2c->SR2;

    i2c->DR = reg;
    result = i2c_wait_flag(i2c, (1 << 7), hi2c->timeout);
    if (result != I2C_OK) return result;

    i2c->CR1 |= (1 << 8); // RESTART
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout);
    if (result != I2C_OK) return result;

    i2c->DR = (hi2c->dev_addr << 1) | I2C_READ;
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout);
    if (result != I2C_OK) return result;
    (void)i2c->SR2;

    i2c->CR1 &= ~(1 << 10); // NACK
    result = i2c_wait_flag(i2c, (1 << 6), hi2c->timeout); // RXNE
    if (result != I2C_OK) return result;

    *data = i2c->DR;
    i2c->CR1 |= (1 << 9); // STOP
    return I2C_OK;
}

uint8_t i2c_driver_write_burst(i2c_handle_t *hi2c, uint8_t reg, uint8_t *data, uint16_t len) {
    I2C_TypeDef *i2c = hi2c->instance;
    uint8_t result;
    uint16_t i;

    i2c->CR1 |= (1 << 8);
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout);
    if (result != I2C_OK) return result;

    i2c->DR = (hi2c->dev_addr << 1) | I2C_WRITE;
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout);
    if (result != I2C_OK) return result;
    (void)i2c->SR2;

    i2c->DR = reg;
    result = i2c_wait_flag(i2c, (1 << 7), hi2c->timeout);
    if (result != I2C_OK) return result;

    for (i = 0; i < len; i++) {
        i2c->DR = data[i];
        result = i2c_wait_flag(i2c, (1 << 7), hi2c->timeout);
        if (result != I2C_OK) return result;
    }

    i2c->CR1 |= (1 << 9);
    return I2C_OK;
}

uint8_t i2c_driver_read_burst(i2c_handle_t *hi2c, uint8_t reg, uint8_t *data, uint16_t len) {
    I2C_TypeDef *i2c = hi2c->instance;
    uint8_t result;
    uint16_t i;

    i2c->CR1 |= (1 << 8);
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout);
    if (result != I2C_OK) return result;

    i2c->DR = (hi2c->dev_addr << 1) | I2C_WRITE;
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout);
    if (result != I2C_OK) return result;
    (void)i2c->SR2;

    i2c->DR = reg;
    result = i2c_wait_flag(i2c, (1 << 7), hi2c->timeout);
    if (result != I2C_OK) return result;

    i2c->CR1 |= (1 << 8);
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout);
    if (result != I2C_OK) return result;

    i2c->DR = (hi2c->dev_addr << 1) | I2C_READ;
    result = i2c_wait_flag(i2c, (1 << 10), hi2c->timeout);
    if (result != I2C_OK) return result;
    (void)i2c->SR2;

    for (i = 0; i < len; i++) {
        if (i == len - 1) {
            i2c->CR1 &= ~(1 << 10);
        }
        result = i2c_wait_flag(i2c, (1 << 6), hi2c->timeout);
        if (result != I2C_OK) return result;
        data[i] = i2c->DR;
    }

    i2c->CR1 |= (1 << 9);
    return I2C_OK;
}

uint8_t i2c_driver_scan_bus(I2C_TypeDef *i2c, uint8_t *found_addrs, uint8_t *count) {
    uint8_t addr;
    uint8_t found = 0;

    for (addr = 0x08; addr < 0x78; addr++) {
        i2c->CR1 |= (1 << 8);
        uint32_t timeout = 10000;
        while (!(i2c->SR1 & (1 << 10))) {
            if (--timeout == 0) break;
        }
        if (timeout == 0) {
            i2c->CR1 |= (1 << 9);
            continue;
        }

        i2c->DR = (addr << 1);
        timeout = 10000;
        while (!(i2c->SR1 & (1 << 10)) && !(i2c->SR1 & (1 << 10))) {
            if (--timeout == 0) break;
        }

        if (timeout == 0) {
            i2c->CR1 |= (1 << 9);
            continue;
        }

        if (i2c->SR1 & (1 << 10)) {
            (void)i2c->SR2;
            found_addrs[found++] = addr;
        } else if (i2c->SR1 & (1 << 10)) {
            (void)i2c->SR2;
        }

        i2c->CR1 |= (1 << 9);
        hal_delay_us(10);
    }

    *count = found;
    return I2C_OK;
}
