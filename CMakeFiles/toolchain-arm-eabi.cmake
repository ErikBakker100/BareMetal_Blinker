set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/14.3 rel1/bin")

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)

set(CMAKE_C_FLAGS "-Wall -nostdlib -nostartfiles -ffreestanding" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_DEBUG "-Wall -nostdlib -nostartfiles -ffreestanding -g3 -Og" CACHE STRING "" FORCE)

set(CMAKE_ASM_FLAGS "--warn --fatal-warnings" CACHE STRING "" FORCE)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
