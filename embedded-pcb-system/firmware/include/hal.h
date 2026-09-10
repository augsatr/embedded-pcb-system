#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <stdbool.h>

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
} I2C_TypeDef;

typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t SR;
    uint32_t DR;
    uint32_t CRCPR;
    uint32_t RXCRCR;
    uint32_t TXCRCR;
    uint32_t I2SCFGR;
    uint32_t I2SPR;
} SPI_TypeDef;

typedef struct {
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
} GPIO_TypeDef;

typedef struct {
    uint32_t CR;
    uint32_t LOAD;
    uint32_t VAL;
    uint32_t CALIB;
} SysTick_TypeDef;

#define I2C1_BASE   0x40005400
#define I2C2_BASE   0x40005800
#define SPI1_BASE   0x40013000
#define SPI2_BASE   0x40003800
#define GPIOA_BASE  0x40010800
#define GPIOB_BASE  0x40010C00
#define GPIOC_BASE  0x40011000
#define RCC_BASE    0x40021000
#define FLASH_BASE  0x40022000
#define AFIO_BASE   0x40010000
#define EXTI_BASE   0x40010400
#define NVIC_BASE   0xE000E100
#define SYSTICK     ((SysTick_TypeDef *)0xE000E010)

#define I2C1        ((I2C_TypeDef *)I2C1_BASE)
#define I2C2        ((I2C_TypeDef *)I2C2_BASE)
#define SPI1        ((SPI_TypeDef *)SPI1_BASE)
#define SPI2        ((SPI_TypeDef *)SPI2_BASE)
#define GPIOA       ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB       ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC       ((GPIO_TypeDef *)GPIOC_BASE)

#define RCC_CR      (*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_CFGR    (*(volatile uint32_t *)(RCC_BASE + 0x04))
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x1C))

#define RCC_APB2ENR_IOPAEN  (1 << 2)
#define RCC_APB2ENR_IOPBEN  (1 << 3)
#define RCC_APB2ENR_IOPCEN  (1 << 4)
#define RCC_APB2ENR_SPI1EN  (1 << 12)
#define RCC_APB1ENR_I2C1EN  (1 << 21)
#define RCC_APB1ENR_I2C2EN  (1 << 22)
#define RCC_APB1ENR_SPI2EN  (1 << 14)

#define GPIO_CRL(port)   (*(volatile uint32_t *)((uint32_t)port + 0x00))
#define GPIO_CRH(port)   (*(volatile uint32_t *)((uint32_t)port + 0x04))
#define GPIO_IDR(port)   (*(volatile uint32_t *)((uint32_t)port + 0x08))
#define GPIO_ODR(port)   (*(volatile uint32_t *)((uint32_t)port + 0x0C))
#define GPIO_BSRR(port)  (*(volatile uint32_t *)((uint32_t)port + 0x10))

void hal_init(void);
void hal_delay_ms(uint32_t ms);
void hal_delay_us(uint32_t us);
uint32_t hal_get_tick(void);

void hal_gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);
void hal_gpio_write(GPIO_TypeDef *port, uint8_t pin, bool state);
bool hal_gpio_read(GPIO_TypeDef *port, uint8_t pin);

uint8_t hal_i2c_init(I2C_TypeDef *i2c, uint32_t clock_speed);
uint8_t hal_i2c_start(I2C_TypeDef *i2c);
uint8_t hal_i2c_stop(I2C_TypeDef *i2c);
uint8_t hal_i2c_send_address(I2C_TypeDef *i2c, uint8_t address, bool rw);
uint8_t hal_i2c_send_data(I2C_TypeDef *i2c, uint8_t data);
uint8_t hal_i2c_receive_data(I2C_TypeDef *i2c, uint8_t *data, bool ack);
uint8_t hal_i2c_write_reg(I2C_TypeDef *i2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
uint8_t hal_i2c_read_reg(I2C_TypeDef *i2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data);
uint8_t hal_i2c_read_burst(I2C_TypeDef *i2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

uint8_t hal_spi_init(SPI_TypeDef *spi, uint8_t prescaler);
uint8_t hal_spi_transfer(SPI_TypeDef *spi, uint8_t data);
uint8_t hal_spi_transfer_byte(SPI_TypeDef *spi, uint8_t data);
void hal_spi_cs_low(GPIO_TypeDef *port, uint8_t pin);
void hal_spi_cs_high(GPIO_TypeDef *port, uint8_t pin);

#endif
