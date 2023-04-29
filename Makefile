# Directories
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = test
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Tools
CC = avr-gcc
MKDIR = mkdir -p

# Options
MCU_FLAGS = -mmcu=atmega328 -DF_CPU=16000000UL
WARNING_FLAGS = -Wall -Wextra -Werror -Wshadow
CFLAGS = $(MCU_FLAGS) $(WARNING_FLAGS) -g -Og

# Files
TARGET = MORT
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TESTS = $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(TEST_SRCS))

.PHONY: all clean flash

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

# Microcontroller flash rule
flash: flash.$(TARGET)
flash.%: $(BIN_DIR)/%
	avrdude -P /dev/ttyUSB0 -c arduino -p atmega328p -b 57600 -U flash:w:$<:e -q -q

clean:
	rm -rf build
