# Hardware Bring-Up Guide

## Pre-Assembly Checklist

1. Verify all components are in stock
2. Check KiCad BOM against inventory
3. Verify PCB gerber files are correct
4. Order PCB fabrication (JLCPCB/PCBWay recommended)

## Assembly Steps

### Step 1: Power Supply Section
1. Solder LM1117-3.3 voltage regulator (U4)
2. Add input/output capacitors (10uF + 100nF)
3. Apply 5V input
4. Verify 3.3V output with multimeter
5. Check current draw (should be <1mA with no load)

### Step 2: Microcontroller
1. Solder STM32F103C8T6 (U1)
2. Add 8MHz crystal oscillator
3. Add 22pF load capacitors
4. Add 10k pull-up on NRST
5. Add 10k pull-down on BOOT0
6. Verify crystal is oscillating (oscilloscope)

### Step 3: I2C Sensors
1. Solder BME280 (U2)
2. Add 4.7k pull-up resistors on SCL/SDA
3. Verify I2C addresses with bus scanner

### Step 4: SPI Sensors
1. Solder LSM6DS3 (U3)
2. Connect CS pin to PA4
3. Verify SPI communication

## Debug Procedures

### Power Supply Verification
- Measure 3.3V at VCC pins
- Check for noise/ripple (<50mV)
- Verify current consumption

### Microcontroller Verification
- Connect ST-Link debugger
- Read device ID (should be 0x1BA01477)
- Flash test firmware
- Verify LED blinking

### I2C Debug
- Monitor SCL/SDA with oscilloscope
- Check pull-up resistor values
- Verify ACK/NACK responses

### SPI Debug
- Monitor MOSI/MISO/SCK with oscilloscope
- Check CS timing
- Verify data transfer rates

## Common Issues

| Issue | Possible Cause | Solution |
|-------|---------------|----------|
| No I2C response | Missing pull-ups | Add 4.7k resistors |
| SPI data corruption | Clock speed too high | Reduce prescaler |
| BME280 returns 0xFF | Wrong I2C address | Try 0x76 or 0x77 |
| LSM6DS3 returns 0x00 | CS not toggling | Check PA4 connection |
| MCU won't start | Missing BOOT0 pulldown | Add 10k to GND |

## Test Points

| Test Point | Expected Value |
|------------|----------------|
| TP1 (3.3V) | 3.3V +/- 5% |
| TP2 (GND) | 0V |
| TP3 (SCL) | 3.3V idle, clock when active |
| TP4 (SDA) | 3.3V idle, data when active |
| TP5 (SCK) | 0V idle, clock when active |
| TP6 (MOSI) | 0V idle |
| TP7 (MISO) | 0V idle |
