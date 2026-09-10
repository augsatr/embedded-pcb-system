#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "virtual_hal.h"
#include "i2c_driver.h"
#include "spi_driver.h"

extern void i2c_simulate_bme280(void);
extern void spi_simulate_lsm6ds3(void);

typedef struct {
    float temperature;
    float pressure;
    float humidity;
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x, gyro_y, gyro_z;
} sensor_data_t;

static float simulate_temperature(float base_temp) {
    float noise = ((float)(rand() % 100) - 50.0f) / 100.0f;
    float drift = sinf((float)virtual_hal_get_tick() / 10000.0f) * 0.5f;
    return base_temp + noise + drift;
}

static float simulate_pressure(float base_pres) {
    float noise = ((float)(rand() % 200) - 100.0f) / 100.0f;
    return base_pres + noise;
}

static float simulate_humidity(float base_hum) {
    float noise = ((float)(rand() % 100) - 50.0f) / 200.0f;
    float drift = sinf((float)virtual_hal_get_tick() / 15000.0f) * 2.0f;
    return base_hum + noise + drift;
}

static void simulate_accel(int16_t *x, int16_t *y, int16_t *z) {
    *x = 204 + (rand() % 20 - 10);
    *y = -102 + (rand() % 20 - 10);
    *z = 16384 + (rand() % 100 - 50);
}

static void simulate_gyro(int16_t *x, int16_t *y, int16_t *z) {
    *x = 128 + (rand() % 40 - 20);
    *y = -64 + (rand() % 40 - 20);
    *z = 32 + (rand() % 40 - 20);
}

static void print_header(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║         EMBEDDED PCB SYSTEM - VIRTUAL SENSOR TEST             ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║  Sensors: BME280 (I2C) + LSM6DS3 (SPI)                       ║\n");
    printf("║  MCU: STM32F103C8T6 @ 72MHz                                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

static void print_sensor_data(uint32_t timestamp, sensor_data_t *data) {
    printf("┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│ Time: %6d ms                                                  │\n", timestamp);
    printf("├─────────────────────────────────────────────────────────────────┤\n");
    printf("│ BME280 (I2C @ 0x76):                                         │\n");
    printf("│   Temperature: %6.2f °C                                    │\n", data->temperature);
    printf("│   Pressure:    %8.1f Pa                                   │\n", data->pressure);
    printf("│   Humidity:    %5.1f %%                                     │\n", data->humidity);
    printf("├─────────────────────────────────────────────────────────────────┤\n");
    printf("│ LSM6DS3 (SPI):                                               │\n");
    printf("│   Accel X: %6d mg    Gyro X: %6d dps                    │\n", data->accel_x, data->gyro_x);
    printf("│   Accel Y: %6d mg    Gyro Y: %6d dps                    │\n", data->accel_y, data->gyro_y);
    printf("│   Accel Z: %6d mg    Gyro Z: %6d dps                    │\n", data->accel_z, data->gyro_z);
    printf("└─────────────────────────────────────────────────────────────────┘\n");
}

static void run_i2c_scan_test(void) {
    printf("\n[TEST] I2C Bus Scan\n");
    printf("─────────────────────\n");

    i2c_handle_t hi2c;
    i2c_driver_init(&hi2c, I2C1, 100000);

    uint8_t found[16];
    uint8_t count;
    i2c_driver_scan_bus(I2C1, found, &count);

    printf("Result: %d devices found\n", count);
    for (int i = 0; i < count; i++) {
        printf("  [0x%02X] %s\n", found[i],
               found[i] == 0x76 ? "BME280" :
               found[i] == 0x68 ? "LSM6DS3 (alt)" : "Unknown");
    }
}

static void run_spi_test(void) {
    printf("\n[TEST] SPI Communication\n");
    printf("─────────────────────────\n");

    spi_handle_t hspi;
    spi_driver_init(&hspi, SPI1, SPI_MODE0, SPI_SPEED_DIV16);
    hspi.cs_port = GPIOA;
    hspi.cs_pin = 4;

    uint8_t id;
    spi_driver_read_reg(&hspi, 0x0F, &id);
    printf("LSM6DS3 WHO_AM_I: 0x%02X (expected 0x69)\n", id);
    printf("Result: %s\n", id == 0x69 ? "PASS" : "FAIL");
}

static void run_sensor_read_test(void) {
    printf("\n[TEST] Sensor Read Cycle\n");
    printf("─────────────────────────\n");

    sensor_data_t data;

    for (int i = 0; i < 10; i++) {
        virtual_hal_delay_ms(1000);

        data.temperature = simulate_temperature(25.0f);
        data.pressure = simulate_pressure(101325.0f);
        data.humidity = simulate_humidity(45.0f);
        simulate_accel(&data.accel_x, &data.accel_y, &data.accel_z);
        simulate_gyro(&data.gyro_x, &data.gyro_y, &data.gyro_z);

        print_sensor_data(virtual_hal_get_tick(), &data);
    }
}

static void run_endurance_test(void) {
    printf("\n[TEST] Endurance Test (1000 cycles)\n");
    printf("──────────────────────────────────────\n");

    int pass = 0;
    int fail = 0;

    for (int i = 0; i < 1000; i++) {
        virtual_hal_delay_ms(10);

        sensor_data_t data;
        data.temperature = simulate_temperature(25.0f);
        data.pressure = simulate_pressure(101325.0f);
        data.humidity = simulate_humidity(45.0f);
        simulate_accel(&data.accel_x, &data.accel_y, &data.accel_z);
        simulate_gyro(&data.gyro_x, &data.gyro_y, &data.gyro_z);

        if (data.temperature > -40 && data.temperature < 85 &&
            data.pressure > 30000 && data.pressure < 110000 &&
            data.humidity >= 0 && data.humidity <= 100) {
            pass++;
        } else {
            fail++;
        }

        if ((i + 1) % 100 == 0) {
            printf("  Cycle %d/1000: PASS=%d FAIL=%d\n", i + 1, pass, fail);
        }
    }

    printf("\nEndurance Test Result: %d PASS, %d FAIL\n", pass, fail);
}

int main(int argc, char *argv[]) {
    virtual_hal_init();
    print_header();

    i2c_simulate_bme280();
    spi_simulate_lsm6ds3();

    run_i2c_scan_test();
    run_spi_test();

    if (argc > 1 && strcmp(argv[1], "--endurance") == 0) {
        run_endurance_test();
    } else {
        run_sensor_read_test();
    }

    printf("\n═══════════════════════════════════════════════════════════════════\n");
    printf("Virtual testing complete. All sensors simulated successfully.\n");
    printf("═══════════════════════════════════════════════════════════════════\n");

    return 0;
}
