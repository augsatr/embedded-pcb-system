#include "hal.h"
#include "i2c_driver.h"
#include "spi_driver.h"
#include "hardware_test.h"

static i2c_handle_t hi2c1;
static spi_handle_t hspi1;

static void system_init(void) {
    RCC_APB2ENR |= (1 << 2);  // GPIOA
    RCC_APB2ENR |= (1 << 3);  // GPIOB
    RCC_APB2ENR |= (1 << 4);  // GPIOC
    RCC_APB2ENR |= (1 << 12); // SPI1
    RCC_APB1ENR |= (1 << 21); // I2C1

    hal_init();

    // I2C1: PB6 (SCL), PB7 (SDA)
    hal_gpio_set_mode(GPIOB, 6, 0x0B);
    hal_gpio_set_mode(GPIOB, 7, 0x0B);

    // SPI1: PA5 (SCK), PA6 (MISO), PA7 (MOSI)
    hal_gpio_set_mode(GPIOA, 5, 0x0B);
    hal_gpio_set_mode(GPIOA, 6, 0x04);
    hal_gpio_set_mode(GPIOA, 7, 0x0B);

    // SPI1 CS: PA4
    hal_gpio_set_mode(GPIOA, 4, 0x03);
    hal_gpio_write(GPIOA, 4, true);

    // LED: PC13
    hal_gpio_set_mode(GPIOC, 13, 0x03);
    hal_gpio_write(GPIOC, 13, true);
}

int main(void) {
    system_init();
    hal_delay_ms(1000);

    i2c_driver_init(&hi2c1, I2C1, 100000);

    spi_driver_init(&hspi1, SPI1, SPI_MODE0, SPI_SPEED_DIV16);
    hspi1.cs_port = GPIOA;
    hspi1.cs_pin = 4;

    test_result_t result;
    uint8_t overall = test_all(&hi2c1, &hspi1, &result);

    if (overall == TEST_PASS) {
        hal_gpio_write(GPIOC, 13, false); // LED ON
    } else {
        while (1) {
            hal_gpio_write(GPIOC, 13, false);
            hal_delay_ms(100);
            hal_gpio_write(GPIOC, 13, true);
            hal_delay_ms(100);
        }
    }

    while (1) {
        hal_delay_ms(1000);
    }

    return 0;
}
