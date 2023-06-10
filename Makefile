# Allow the user to specify the location of the avr-gcc toolchain
ifdef AVR_GCC_DIR
AVR_GCC_BIN_DIR = $(AVR_GCC_DIR)/bin
endif

# Directories
SRC_DIR   = src
BUILD_DIR = build
TEST_DIR  = test
OBJ_DIR   = $(BUILD_DIR)/obj
BIN_DIR   = $(BUILD_DIR)/bin

# Tools
ifdef AVR_GCC_BIN_DIR
CC    = $(AVR_GCC_BIN_DIR)/avr-gcc
else
CC    = avr-gcc
endif
MKDIR = mkdir -p

# Options
MCU_FLAGS           = -mmcu=atmega328 -DF_CPU=16000000UL
WARNING_FLAGS       = -Wall -Wextra -Wpedantic -Werror -Wshadow
CFLAGS              = $(MCU_FLAGS) $(WARNING_FLAGS) -g -Og
AVRDUDE_SERIAL_PORT = /dev/ttyUSB0

# Files
TARGET    = MORT
SRCS      = $(wildcard $(SRC_DIR)/*.c)
HEADERS   = $(wildcard $(SRC_DIR)/*.h)
OBJS      = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TESTS     = $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(TEST_SRCS))

.PHONY: all clean analyze flash

# Build target executable and all tests
all: $(BIN_DIR)/$(TARGET) $(TESTS)

# Executable build rule
$(BIN_DIR)/$(TARGET): $(OBJS)
	@$(MKDIR) $(BIN_DIR)
	$(CC) $^ -o $@ $(CFLAGS)

# Test build rule (prevent redefinition of main function)
$(BIN_DIR)/test_%: $(TEST_DIR)/test_%.c $(filter-out $(OBJ_DIR)/main.o, $(OBJS))
	@$(MKDIR) $(BIN_DIR)
	$(CC) $^ -o $@ -I$(SRC_DIR) $(CFLAGS)

# Object build rule, .c with header
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	@$(MKDIR) $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Object build rule, .c without header
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Formatting rule
format:
	@clang-format-12 -i $(SRCS) $(HEADERS)

# Static analysis rule
analyze:
	cppcheck src/ --enable=all --suppress=missingIncludeSystem --error-exitcode=1 --quiet

# Microcontroller flash rule
flash: flash.$(TARGET)
flash.%: $(BIN_DIR)/%
	avrdude -P $(AVRDUDE_SERIAL_PORT) -c arduino -p atmega328p -b 57600 -U flash:w:$<:e -q -q

clean:
	rm -rf build
