CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CPU = -mcpu=cortex-m3 -mthumb

CFLAGS = $(CPU) -Os -Wall -Wextra -I../include -I../drivers
CFLAGS += -ffunction-sections -fdata-sections -fno-common
CFLAGS += -DSTM32F103xB

LDFLAGS = $(CPU) -specs=nosys.specs -specs=nano.specs -Wl,--gc-sections
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/firmware.map

BUILD_DIR = build
SRC_DIR = src
DRIVER_DIR = drivers
TEST_DIR = tests

SOURCES = $(SRC_DIR)/hal.c $(SRC_DIR)/main.c
SOURCES += $(DRIVER_DIR)/i2c_driver.c $(DRIVER_DIR)/spi_driver.c
SOURCES += $(DRIVER_DIR)/bme280.c $(DRIVER_DIR)/lsm6ds3.c

TEST_SOURCES = $(TEST_DIR)/test_main.c $(TEST_DIR)/hardware_test.c
TEST_SOURCES += $(SRC_DIR)/hal.c $(DRIVER_DIR)/i2c_driver.c $(DRIVER_DIR)/spi_driver.c
TEST_SOURCES += $(DRIVER_DIR)/bme280.c $(DRIVER_DIR)/lsm6ds3.c

OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.c=.o)))
TEST_OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SOURCES:.c=.o)))

ELF = $(BUILD_DIR)/firmware.elf
HEX = $(BUILD_DIR)/firmware.hex
BIN = $(BUILD_DIR)/firmware.bin
TEST_ELF = $(BUILD_DIR)/test.elf
TEST_HEX = $(BUILD_DIR)/test.hex

vpath %.c $(SRC_DIR) $(DRIVER_DIR) $(TEST_DIR)

.PHONY: all clean flash test

all: $(BUILD_DIR) $(HEX) $(BIN)
	$(SIZE) $(ELF)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

test: $(BUILD_DIR) $(TEST_HEX)
	$(SIZE) $(TEST_ELF)

$(TEST_ELF): $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(TEST_HEX): $(TEST_ELF)
	$(OBJCOPY) -O ihex $< $@

flash: $(HEX)
	st-flash --format ihex write $(HEX)

flash-test: $(TEST_HEX)
	st-flash --format ihex write $(TEST_HEX)

clean:
	rm -rf $(BUILD_DIR)

debug: $(ELF)
	arm-none-eabi-gdb $(ELF) -ex "target remote :3333"
