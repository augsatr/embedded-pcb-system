#ifndef VIRTUAL_HAL_H
#define VIRTUAL_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HAL_OK      0
#define HAL_ERROR   1
#define HAL_BUSY    2
#define HAL_TIMEOUT 3

typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t OAR1;
    uint32_t OAR2;
    uint32_t DR;
    uint32_t SR1;
    uint32_t SR2;
    uint32_t CCR;
    uint32_t TRISE;
    uint8_t  rx_buffer[256];
    uint8_t  tx_buffer[256];
    uint8_t  rx_head;
    uint8_t  tx_head;
} Virtual_I2C;

typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t SR;
    uint32_t DR;
    uint32_t CRCPR;
    uint32_t RXCRCR;
    uint32_t TXCRCR;
    uint8_t  rx_buffer[256];
    uint8_t  tx_buffer[256];
    uint8_t  rx_head;
    uint8_t  tx_head;
} Virtual_SPI;

typedef struct {
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
} Virtual_GPIO;

extern Virtual_I2C  virtual_i2c1;
extern Virtual_I2C  virtual_i2c2;
extern Virtual_SPI  virtual_spi1;
extern Virtual_SPI  virtual_spi2;
extern Virtual_GPIO virtual_gpioa;
extern Virtual_GPIO virtual_gpiob;
extern Virtual_GPIO virtual_gpioc;

#define I2C1  (&virtual_i2c1)
#define I2C2  (&virtual_i2c2)
#define SPI1  (&virtual_spi1)
#define SPI2  (&virtual_spi2)
#define GPIOA (&virtual_gpioa)
#define GPIOB (&virtual_gpiob)
#define GPIOC (&virtual_gpioc)

typedef Virtual_I2C I2C_TypeDef;
typedef Virtual_SPI SPI_TypeDef;
typedef Virtual_GPIO GPIO_TypeDef;

void virtual_hal_init(void);
void virtual_hal_delay_ms(uint32_t ms);
void virtual_hal_delay_us(uint32_t us);
uint32_t virtual_hal_get_tick(void);

void virtual_gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);
void virtual_gpio_write(GPIO_TypeDef *port, uint8_t pin, bool state);
bool virtual_gpio_read(GPIO_TypeDef *port, uint8_t pin);

void virtual_i2c_reset(Virtual_I2C *i2c);
void virtual_spi_reset(Virtual_SPI *spi);

void virtual_i2c_simulate_slave(Virtual_I2C *i2c, uint8_t dev_addr, uint8_t *data, uint16_t len);
void virtual_spi_simulate_device(Virtual_SPI *spi, uint8_t *tx_data, uint8_t len);

#define hal_init virtual_hal_init
#define hal_delay_ms virtual_hal_delay_ms
#define hal_delay_us virtual_hal_delay_us
#define hal_get_tick virtual_hal_get_tick

#define hal_gpio_set_mode virtual_gpio_set_mode
#define hal_gpio_write virtual_gpio_write
#define hal_gpio_read virtual_gpio_read

#define RCC_APB2ENR_IOPAEN  (1 << 2)
#define RCC_APB2ENR_IOPBEN  (1 << 3)
#define RCC_APB2ENR_IOPCEN  (1 << 4)
#define RCC_APB2ENR_SPI1EN  (1 << 12)
#define RCC_APB1ENR_I2C1EN  (1 << 21)
#define RCC_APB1ENR_I2C2EN  (1 << 22)
#define RCC_APB1ENR_SPI2EN  (1 << 14)

static uint32_t RCC_APB2ENR_val = 0;
static uint32_t RCC_APB1ENR_val = 0;
#define RCC_APB2ENR RCC_APB2ENR_val
#define RCC_APB1ENR RCC_APB1ENR_val

#endif
