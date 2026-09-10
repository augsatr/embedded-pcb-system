# Embedded PCB System - Sensor Interface Board

Custom PCB-based embedded system for multi-sensor data acquisition using I2C and SPI interfaces.

## Overview

This project implements a custom printed circuit board (PCB) designed for interfacing with multiple sensors via I2C and SPI communication protocols. The system uses an STM32F103C8T6 microcontroller (Blue Pill compatible) as the main processing unit.

## Features

- **Microcontroller**: STM32F103C8T6 (ARM Cortex-M3, 72MHz, 64KB Flash, 20KB SRAM)
- **I2C Interface**: Connected to BME280 temperature/pressure/humidity sensor
- **SPI Interface**: Connected to LSM6DS3 6-axis IMU (accelerometer + gyroscope)
- **Power Supply**: 3.3V LDO voltage regulator (LM1117-3.3)
- **Pin Headers**: I2C and SPI breakout headers for external connections

## PCB Design

Designed in KiCad with the following specifications:
- **Board Size**: 160mm x 120mm
- **Layers**: 2-layer (F.Cu, B.Cu)
- **Track Width**: 0.25mm (signal), 0.5mm (power)
- **Via Size**: 0.6mm diameter, 0.3mm drill
- **Clearance**: 0.2mm

### Bill of Materials

| Ref | Component | Package | Value |
|-----|-----------|---------|-------|
| U1 | STM32F103C8T6 | LQFP-48 | Microcontroller |
| U2 | BME280 | SMD | Temp/Pressure/Humidity |
| U3 | LSM6DS3TR | SMD | 6-axis IMU |
| U4 | LM1117-3.3 | SOT-223 | 3.3V LDO |
| J1 | Pin Header 1x6 | 2.54mm | I2C Header |
| J2 | Pin Header 1x8 | 2.54mm | SPI Header |

## Firmware

Embedded C firmware for STM32F103C8T6 microcontroller.

### Project Structure

```
firmware/
├── include/
│   ├── hal.h          # Hardware Abstraction Layer
│   └── debug.h        # Debug UART interface
├── drivers/
│   ├── i2c_driver.h/c # I2C communication driver
│   ├── spi_driver.h/c # SPI communication driver
│   ├── bme280.h/c     # BME280 sensor driver
│   └── lsm6ds3.h/c    # LSM6DS3 IMU driver
├── src/
│   ├── hal.c          # HAL implementation
│   ├── main.c         # Main application
│   └── debug.c        # Debug console
├── tests/
│   ├── hardware_test.h/c # Hardware test suite
│   └── test_main.c       # Test runner
└── Makefile           # Build system
```

### Build

```bash
# Install ARM toolchain
# Windows: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm
# Linux: sudo apt install gcc-arm-none-eabi

cd firmware
make all

# Run tests
make test

# Flash firmware
make flash
```

### Pin Mapping

#### I2C1 (BME280)
| Pin | Function | Description |
|-----|----------|-------------|
| PB6 | SCL | I2C Clock |
| PB7 | SDA | I2C Data |

#### SPI1 (LSM6DS3)
| Pin | Function | Description |
|-----|----------|-------------|
| PA5 | SCK | SPI Clock |
| PA6 | MISO | Master In Slave Out |
| PA7 | MOSI | Master Out Slave In |
| PA4 | NSS | Slave Select (Active Low) |

### Sensor Addresses

- **BME280**: 0x76 (or 0x77 with SDO high)
- **LSM6DS3**: SPI communication (CS on PA4)

## Hardware Testing

The test suite covers:
1. I2C bus scan and communication
2. SPI loopback test
3. BME280 temperature/pressure/humidity readings
4. LSM6DS3 accelerometer and gyroscope readings
5. GPIO output verification
6. Power supply voltage check

Run tests via UART debug console or ST-Link debugger.

## Debug Console

UART debug output at 115200 baud on PA9 (TX) / PA10 (RX):
```
Embedded PCB System - Debug Console
====================================
Scanning I2C bus...
Found 1 devices:
  0x76
BME280: T=25.43 P=101325 H=45.21
LSM6DS3 Accel: X=204 Y=-102 Z=16384
```

## Tools Used

- **KiCad**: PCB schematic and layout design
- **Embedded C**: Firmware development
- **ARM GCC**: Cross-compilation toolchain
- **ST-Link**: On-chip debugging and flashing
- **Serial Terminal**: Debug console (115200 baud)

## License

MIT License - SIH Hackathon Project
