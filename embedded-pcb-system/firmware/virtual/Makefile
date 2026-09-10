CC = gcc
CFLAGS = -Wall -Wextra -I./ -I../include -DSTM32F103xB
LDFLAGS = -lm

BUILD_DIR = build
SOURCES = virtual_hal.c i2c_driver.c spi_driver.c virtual_test.c
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:.c=.o))
ELF = $(BUILD_DIR)/virtual_test

vpath %.c .

.PHONY: all clean run test endurance python

all: $(BUILD_DIR) $(ELF)
	@echo "Build complete. Run with: ./build/virtual_test"

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Virtual test binary created: $(ELF)"

run: all
	./$(ELF)

test: all
	./$(ELF)

endurance: all
	./$(ELF) --endurance

python:
	python sensor_simulator.py 30

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "Virtual Testing Commands:"
	@echo "  make all       - Build virtual test binary"
	@echo "  make run       - Run virtual sensor simulation"
	@echo "  make test      - Run basic tests"
	@echo "  make endurance - Run 1000-cycle endurance test"
	@echo "  make python    - Run Python visual simulator"
	@echo "  make clean     - Clean build artifacts"
