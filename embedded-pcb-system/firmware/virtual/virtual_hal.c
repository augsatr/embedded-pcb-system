#include "virtual_hal.h"

Virtual_I2C  virtual_i2c1 = {0};
Virtual_I2C  virtual_i2c2 = {0};
Virtual_SPI  virtual_spi1 = {0};
Virtual_SPI  virtual_spi2 = {0};
Virtual_GPIO virtual_gpioa = {0};
Virtual_GPIO virtual_gpiob = {0};
Virtual_GPIO virtual_gpioc = {0};

static uint32_t virtual_tick = 0;

void virtual_hal_init(void) {
    srand((unsigned int)time(NULL));
    virtual_tick = 0;
    printf("[VIRTUAL] HAL initialized\n");
}

void virtual_hal_delay_ms(uint32_t ms) {
    virtual_tick += ms;
}

void virtual_hal_delay_us(uint32_t us) {
    virtual_tick += us / 1000;
}

uint32_t virtual_hal_get_tick(void) {
    return virtual_tick;
}

void virtual_gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode) {
    volatile uint32_t *cr;
    uint8_t shift;

    if (pin < 8) {
        cr = &port->CRL;
        shift = pin * 4;
    } else {
        cr = &port->CRH;
        shift = (pin - 8) * 4;
    }

    *cr = (*cr & ~(0xF << shift)) | ((mode & 0xF) << shift);
    printf("[VIRTUAL] GPIO pin %d mode set to 0x%02X\n", pin, mode);
}

void virtual_gpio_write(GPIO_TypeDef *port, uint8_t pin, bool state) {
    if (state) {
        port->ODR |= (1 << pin);
        port->IDR |= (1 << pin);
    } else {
        port->ODR &= ~(1 << pin);
        port->IDR &= ~(1 << pin);
    }
}

bool virtual_gpio_read(GPIO_TypeDef *port, uint8_t pin) {
    return (port->IDR & (1 << pin)) != 0;
}

void virtual_i2c_reset(Virtual_I2C *i2c) {
    memset(i2c, 0, sizeof(Virtual_I2C));
    i2c->SR2 = 0x00; // Not busy
}

void virtual_spi_reset(Virtual_SPI *spi) {
    memset(spi, 0, sizeof(Virtual_SPI));
}

void virtual_i2c_simulate_slave(Virtual_I2C *i2c, uint8_t dev_addr, uint8_t *data, uint16_t len) {
    uint16_t i;
    for (i = 0; i < len && i < 256; i++) {
        i2c->rx_buffer[i] = data[i];
    }
    i2c->rx_head = (uint8_t)len;
    printf("[VIRTUAL] I2C slave 0x%02X loaded with %d bytes\n", dev_addr, len);
}

void virtual_spi_simulate_device(Virtual_SPI *spi, uint8_t *tx_data, uint8_t len) {
    uint16_t i;
    for (i = 0; i < len && i < 256; i++) {
        spi->rx_buffer[i] = tx_data[i];
    }
    spi->rx_head = (uint8_t)len;
    printf("[VIRTUAL] SPI slave loaded with %d bytes\n", len);
}
