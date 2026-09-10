#include "hal.h"
#include "i2c_driver.h"
#include "bme280.h"

#ifdef DEBUG
#define UART_PRINT(str) debug_uart_send_str(str)
#else
#define UART_PRINT(str) ((void)0)
#endif

static void debug_uart_init(void) {
    RCC_APB2ENR |= (1 << 14); // USART1
    // Baud rate 115200 @ 72MHz
    *(volatile uint32_t *)0x4001380C = 39; // BRR
    *(volatile uint32_t *)0x4001380C |= (1 << 13) | (1 << 3); // TE, UE
}

static void debug_uart_send_char(char c) {
    uint32_t * USART1_SR = (uint32_t *)0x40013800;
    uint32_t * USART1_DR = (uint32_t *)0x40013804;
    while (!(*USART1_SR & (1 << 7)));
    *USART1_DR = (uint32_t)c;
}

void debug_uart_send_str(const char *str) {
    while (*str) {
        debug_uart_send_char(*str++);
    }
}

void debug_uart_send_num(int32_t num) {
    char buf[12];
    int i = 0;
    int neg = 0;

    if (num < 0) {
        neg = 1;
        num = -num;
    }

    if (num == 0) {
        buf[i++] = '0';
    } else {
        while (num > 0) {
            buf[i++] = '0' + (num % 10);
            num /= 10;
        }
    }

    if (neg) {
        debug_uart_send_char('-');
    }

    while (i > 0) {
        debug_uart_send_char(buf[--i]);
    }
}

void debug_init(void) {
    debug_uart_init();
    UART_PRINT("Embedded PCB System - Debug Console\r\n");
    UART_PRINT("====================================\r\n");
}

void debug_i2c_scan(I2C_TypeDef *i2c) {
    UART_PRINT("Scanning I2C bus...\r\n");
    uint8_t found[16];
    uint8_t count;
    i2c_driver_scan_bus(i2c, found, &count);

    UART_PRINT("Found ");
    debug_uart_send_num(count);
    UART_PRINT(" devices:\r\n");

    uint8_t i;
    for (i = 0; i < count; i++) {
        UART_PRINT("  0x");
        if (found[i] < 0x10) UART_PRINT("0");
        debug_uart_send_num(found[i]);
        UART_PRINT("\r\n");
    }
}

void debug_bme280_data(float temp, float pres, float hum) {
    UART_PRINT("BME280: T=");
    debug_uart_send_num((int32_t)(temp * 100));
    UART_PRINT(" P=");
    debug_uart_send_num((int32_t)pres);
    UART_PRINT(" H=");
    debug_uart_send_num((int32_t)(hum * 100));
    UART_PRINT("\r\n");
}

void debug_lsm6ds3_data(lsm6ds3_axis_t accel, lsm6ds3_axis_t gyro) {
    UART_PRINT("LSM6DS3 Accel: X=");
    debug_uart_send_num(accel.x);
    UART_PRINT(" Y=");
    debug_uart_send_num(accel.y);
    UART_PRINT(" Z=");
    debug_uart_send_num(accel.z);
    UART_PRINT("\r\n");

    UART_PRINT("LSM6DS3 Gyro:  X=");
    debug_uart_send_num(gyro.x);
    UART_PRINT(" Y=");
    debug_uart_send_num(gyro.y);
    UART_PRINT(" Z=");
    debug_uart_send_num(gyro.z);
    UART_PRINT("\r\n");
}
