# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2026-09-10

### Added
- Initial release
- KiCad PCB design (schematic + layout)
- STM32F103C8T6 firmware
- Hardware Abstraction Layer (HAL)
- I2C driver for BME280 sensor
- SPI driver for LSM6DS3 IMU
- Hardware test suite
- Virtual testing environment (C simulation)
- Python sensor simulator
- Web-based dashboard with 7 tabs
- Protocol analyzer (I2C/SPI traffic)
- Pin state viewer
- Register dump viewer
- Alarm system with configurable thresholds
- Simulation modes (Normal, Stress, Fault, Drift, Random)
- Data export (JSON, CSV)
- Complete documentation
- MIT License

### Hardware
- STM32F103C8T6 microcontroller (LQFP-48)
- BME280 temperature/pressure/humidity sensor (I2C)
- LSM6DS3 6-axis IMU (SPI)
- LM1117-3.3V voltage regulator
- I2C breakout header (6-pin)
- SPI breakout header (8-pin)
- 8MHz crystal oscillator
- Decoupling capacitors
- Status LED

### Firmware
- Clock initialization (72MHz HSE + PLL)
- GPIO configuration
- I2C1 driver (100kHz)
- SPI1 driver (4.5MHz, Mode 0)
- BME280 driver with compensation algorithm
- LSM6DS3 driver with full register access
- Debug UART (115200 baud)
- Hardware test suite (10 tests)

### Virtual Testing
- Mock HAL layer for PC simulation
- Simulated I2C/SPI communication
- BME280 register simulation
- LSM6DS3 register simulation
- C-based test runner
- Python sensor simulator
- Web dashboard (HTML/JS/CSS)

### Documentation
- System architecture diagrams
- PCB layout diagrams
- Firmware architecture diagrams
- I2C/SPI timing diagrams
- Pin mapping diagrams
- Testing workflow diagrams
- Complete API documentation
- Troubleshooting guide
- FAQ section

---

## [1.1.0] - Planned

### Added
- More sensor drivers (BMP280, MPU6050, etc.)
- RTOS support (FreeRTOS)
- WiFi/Bluetooth connectivity
- Mobile application
- Cloud data logging
- Battery management
- Low power modes
- SD card data logging
- More simulation modes
- Advanced data visualization

### Changed
- Improved code organization
- Better error handling
- Enhanced documentation
- Performance optimizations

### Fixed
- Known issues from v1.0.0

---

## [1.2.0] - Future

### Added
- Machine learning integration
- Predictive maintenance
- Remote monitoring
- Multi-device support
- Web API
- Database integration
- User authentication
- Data analytics

---

## Version History

| Version | Date | Description |
|---------|------|-------------|
| 1.0.0 | 2026-09-10 | Initial release |
| 1.1.0 | TBD | Enhanced features |
| 1.2.0 | TBD | Advanced capabilities |

---

## Upgrade Guide

### From 1.0.0 to 1.1.0

1. Backup your code
2. Pull latest changes
3. Review breaking changes
4. Update your code
5. Test thoroughly

---

## Support

For issues and questions, please open an issue on [GitHub Issues](https://github.com/augsatr/embedded-pcb-system/issues).
