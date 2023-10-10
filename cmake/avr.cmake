set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          AVR)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(_toolchain_prefix  "avr")

if (DEFINED ENV{AVR_TOOLCHAIN_DIR})
    set(_toolchain_prefix $ENV{AVR_TOOLCHAIN_DIR}/bin/${_toolchain_prefix})
endif()

message(STATUS "Using AVR toolchain prefix: ${_toolchain_prefix}")

set(CMAKE_AR           ${_toolchain_prefix}-ar${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_ASM_COMPILER ${_toolchain_prefix}-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_C_COMPILER   ${_toolchain_prefix}-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_CXX_COMPILER ${_toolchain_prefix}-g++${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_LINKER       ${_toolchain_prefix}-ld${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJCOPY      ${_toolchain_prefix}-objcopy${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_RANLIB       ${_toolchain_prefix}-ranlib${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_SIZE         ${_toolchain_prefix}-size${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_STRIP        ${_toolchain_prefix}-strip${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_GCOV         ${_toolchain_prefix}-gcov${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")

# C Flags
set(TOOLCHAIN_MCU atmega328p)
set(TOOLCHAIN_C_FLAGS -mmcu=${TOOLCHAIN_MCU} -Os -Wall -Wextra -Wpedantic -Werror -Wshadow)

# C Definitions
set(_c_defs
    -DF_CPU=16000000UL)

# C++ Flags
set(_cxx_flags
    ${_c_flags}
    -fno-exceptions
    -fno-rtti)

# C++ Definitions
set(_cxx_defs ${_c_defs})

#list(JOIN _c_flags " " TOOLCHAIN_C_FLAGS)
list(JOIN _c_defs " " TOOLCHAIN_C_DEFS)
list(JOIN _cxx_flags " " TOOLCHAIN_CXX_FLAGS)
list(JOIN _cxx_defs " " TOOLCHAIN_CXX_DEFS)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
