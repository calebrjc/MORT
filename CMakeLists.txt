cmake_minimum_required(VERSION 3.12)
project(MORT)

set(HEADERS)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE c_std_99)
target_compile_options(${PROJECT_NAME} PRIVATE ${TOOLCHAIN_C_FLAGS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${TOOLCHAIN_C_DEFS})

# Post-Build Steps ---------------------------------------------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")

# Custom command to print the size of the binary
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
   COMMAND ${CMAKE_SIZE} ARGS 
       -A "$<TARGET_FILE:${PROJECT_NAME}>"
   USES_TERMINAL)

# Custom command to generate the .eep file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
   BYPRODUCTS ${PROJECT_NAME}.eep
   COMMAND ${CMAKE_OBJCOPY} ARGS 
       -O ihex -j .eeprom
       --set-section-flags=.eeprom=alloc,load
       --no-change-warnings --change-section-lma 
       .eeprom=0
       "$<TARGET_FILE:${PROJECT_NAME}>"
       ${PROJECT_NAME}.eep)

# Custom command to generate the .hex file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
   BYPRODUCTS ${PROJECT_NAME}.hex
   COMMAND ${CMAKE_OBJCOPY} ARGS 
       -O ihex -R .eeprom
       "$<TARGET_FILE:${PROJECT_NAME}>"
       ${PROJECT_NAME}.hex)

# Upload -------------------------------------------------------------------------------------------
set(UPLOAD_PORT COM3)
set(UPLOAD_SPEED 115200)
set(UPLOAD_PROTOCOL arduino)

# Create a custom command to flash using avrdude
add_custom_target(
    flash
    COMMAND avrdude -p ${TOOLCHAIN_MCU} -c ${UPLOAD_PROTOCOL} -P ${UPLOAD_PORT} -b ${UPLOAD_SPEED} -U flash:w:${PROJECT_NAME}.hex:i -q -q
    DEPENDS ${PROJECT_NAME}
    COMMENT "Flashing ${PROJECT_NAME} to ${TOOLCHAIN_MCU} using ${UPLOAD_PROTOCOL} on port ${UPLOAD_PORT} at ${UPLOAD_SPEED} baud"
    VERBATIM
)

# Formatting and Linting ---------------------------------------------------------------------------

# Create a custom target to run clang-format
add_custom_target(
    format
    COMMAND clang-format -i ${HEADERS} ${SOURCES}
    COMMENT "Formatting ${PROJECT_NAME} with clang-format"
    VERBATIM
)

# Create a custom target to run cppcheck
add_custom_target(
    analyze
    COMMAND cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=unusedStructMember --suppress=unusedVariable --suppress=missingInclude --suppress=unmatchedSuppression ${HEADERS} ${SOURCES}
    COMMENT "Linting ${PROJECT_NAME} with cppcheck"
    VERBATIM
)
