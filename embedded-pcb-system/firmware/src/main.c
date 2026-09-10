#include "hal.h"
#include "i2c_driver.h"
#include "spi_driver.h"
#include "bme280.h"
#include "lsm6ds3.h"

static i2c_handle_t hi2c1;
static spi_handle_t hspi1;
static bme280_handle_t hbme280;
static lsm6ds3_handle_t hlsm6ds3;

static void clock_init(void) {
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC_APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC_APB2ENR |= RCC_APB2ENR_SPI1EN;
    RCC_APB1ENR |= RCC_APB1ENR_I2C1EN;
}

static void gpio_init(void) {
    // I2C1: PB6 (SCL), PB7 (SDA) - AF Open Drain
    hal_gpio_set_mode(GPIOB, 6, 0x0B); // AF Open Drain 50MHz
    hal_gpio_set_mode(GPIOB, 7, 0x0B);

    // SPI1: PA5 (SCK), PA7 (MOSI) - AF Push-Pull
    hal_gpio_set_mode(GPIOA, 5, 0x0B); // AF Push-Pull 50MHz
    hal_gpio_set_mode(GPIOA, 7, 0x0B);
    // SPI1: PA6 (MISO) - Input Floating
    hal_gpio_set_mode(GPIOA, 6, 0x04); // Input Floating

    // SPI1 NSS: PA4 - Output Push-Pull
    hal_gpio_set_mode(GPIOA, 4, 0x03); // Output Push-Pull 50MHz
    hal_gpio_write(GPIOA, 4, true);    // CS high

    // LED: PC13 - Output Push-Pull (active low on Blue Pill)
    hal_gpio_set_mode(GPIOC, 13, 0x03);
    hal_gpio_write(GPIOC, 13, true);   // LED off

    // UART TX: PA9 - AF Push-Pull (for debug)
    hal_gpio_set_mode(GPIOA, 9, 0x0B);
    // UART RX: PA10 - Input Floating
    hal_gpio_set_mode(GPIOA, 10, 0x04);
}

static void system_init(void) {
    clock_init();
    hal_init();
    gpio_init();
}

static void led_toggle(void) {
    static bool state = false;
    state = !state;
    hal_gpio_write(GPIOC, 13, state);
}

static void delay_ms(uint32_t ms) {
    hal_delay_ms(ms);
}

int main(void) {
    system_init();

    delay_ms(1000);

    uint8_t i2c_result = i2c_driver_init(&hi2c1, I2C1, 100000);
    if (i2c_result != I2C_OK) {
        while (1) {
            led_toggle();
            delay_ms(100);
        }
    }

    uint8_t spi_result = spi_driver_init(&hspi1, SPI1, SPI_MODE0, SPI_SPEED_DIV16);
    if (spi_result != SPI_OK) {
        while (1) {
            led_toggle();
            delay_ms(200);
        }
    }

    hspi1.cs_port = GPIOA;
    hspi1.cs_pin = 4;

    uint8_t bme_status = bme280_init(&hbme280, &hi2c1, BME280_I2C_ADDR_0);
    if (bme_status != 0) {
        bme_status = bme280_init(&hbme280, &hi2c1, BME280_I2C_ADDR_1);
    }

    uint8_t lsm_status = lsm6ds3_init(&hlsm6ds3, &hspi1);

    bme280_configure(&hbme280,
        BME280_OVERSAMPLING_2,
        BME280_OVERSAMPLING_16,
        BME280_OVERSAMPLING_1,
        BME280_MODE_NORMAL);

    float temperature, pressure, humidity;
    lsm6ds3_data_t imu_data;

    while (1) {
        if (bme_status == 0) {
            bme280_read_temperature(&hbme280, &temperature);
            bme280_read_pressure(&hbme280, &pressure);
            bme280_read_humidity(&hbme280, &humidity);
        }

        if (lsm_status == 0) {
            lsm6ds3_read_all(&hlsm6ds3, &imu_data);
        }

        led_toggle();
        delay_ms(500);
    }

    return 0;
}
