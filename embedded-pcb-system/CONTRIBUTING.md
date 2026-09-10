# Contributing to Embedded PCB System

Thank you for your interest in contributing! This document provides guidelines and steps for contributing.

## How to Contribute

### 1. Fork the Repository

```bash
# Click the Fork button on GitHub
# Then clone your fork
git clone https://github.com/YOUR_USERNAME/embedded-pcb-system.git
cd embedded-pcb-system
```

### 2. Create a Branch

```bash
# Create a feature branch
git checkout -b feature/amazing-feature

# Or a bug fix branch
git checkout -b fix/bug-description
```

### 3. Make Changes

- Follow the code style guidelines below
- Add comments for complex logic
- Update documentation if needed
- Test your changes on hardware if possible

### 4. Commit Changes

```bash
# Stage your changes
git add .

# Commit with a descriptive message
git commit -m "feat: Add amazing feature"

# Use conventional commit format:
# feat:     New feature
# fix:      Bug fix
# docs:     Documentation changes
# style:    Code style changes
# refactor: Code refactoring
# test:     Adding tests
# chore:    Maintenance tasks
```

### 5. Push and Create PR

```bash
# Push to your fork
git push origin feature/amazing-feature

# Create a Pull Request on GitHub
```

## Code Style Guidelines

### C Code

```c
// Use 4 spaces for indentation
int main(void) {
    // Declare variables at the top
    uint8_t data;
    int result;
    
    // Use descriptive names
    uint8_t sensor_address = 0x76;
    
    // Add comments for complex logic
    // Read temperature compensation coefficients from NVM
    // The formula is: T = ((t_fine * 5 + 128) >> 8)
    
    // Keep functions focused
    if (condition) {
        do_something();
    } else {
        do_something_else();
    }
}
```

### Function Documentation

```c
/**
 * @brief Initialize BME280 sensor
 * 
 * This function initializes the BME280 sensor with the specified
 * I2C address and reads the calibration coefficients.
 * 
 * @param hbme Pointer to BME280 handle structure
 * @param hi2c Pointer to I2C handle structure
 * @param addr I2C address of the sensor (0x76 or 0x77)
 * 
 * @return 0 on success, 1 if chip ID mismatch, 2 on I2C error
 * 
 * @note Must be called before any other BME280 functions
 * @warning Do not call this function while sensor is in measurement mode
 */
uint8_t bme280_init(bme280_handle_t *hbme, i2c_handle_t *hi2c, uint8_t addr);
```

### Naming Conventions

| Element | Convention | Example |
|---------|------------|---------|
| Functions | snake_case | `bme280_read_temperature()` |
| Variables | snake_case | `sensor_address` |
| Constants | UPPER_SNAKE | `BME280_CHIP_ID` |
| Types | _t suffix | `bme280_handle_t` |
| Macros | UPPER_SNAKE | `#define BME280_REG_ID 0xD0` |
| Files | snake_case | `bme280.c`, `i2c_driver.h` |

## Testing Requirements

### Hardware Testing

- Test on real hardware before submitting
- Verify I2C/SPI communication
- Check for memory leaks
- Test edge cases

### Virtual Testing

```bash
# Run virtual tests
cd firmware/virtual
make all
make run

# Run endurance test
make endurance
```

### Web Dashboard Testing

- Open `virtual-dashboard.html` in multiple browsers
- Test all tabs and features
- Verify data export works
- Check responsive design

## Documentation

- Update README.md for new features
- Add inline comments for complex code
- Update API documentation
- Add examples for new functions

## Pull Request Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Code refactoring
- [ ] Test addition

## Testing
- [ ] Tested on hardware
- [ ] Virtual tests pass
- [ ] Web dashboard works

## Checklist
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
- [ ] No breaking changes
```

## Questions?

Feel free to open an issue for any questions about contributing!
