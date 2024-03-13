file(GLOB_RECURSE KLIBC_SOURCES LIST_DIRECTORIES TRUE "${CMAKE_CURRENT_LIST_DIR}/*.c")

add_library(klibc STATIC ${KLIBC_SOURCES})

target_include_directories(klibc
    PRIVATE include
)

target_compile_options(klibc
    PRIVATE -Werror
    PRIVATE -ffreestanding
    PRIVATE -nostdlib
    PRIVATE -fno-omit-frame-pointer
    PRIVATE -fno-stack-protector
    PRIVATE -fno-pic
    PRIVATE -fno-pie
    PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    PRIVATE $<$<C_COMPILER_ID:Clang>:-target x86_64-pc-elf>
)

if(${PARENT_PROJECT_NAME}_ARCHITECTURE STREQUAL x86_64)
    target_compile_options(klibc
        PRIVATE -march=x86-64
        PRIVATE -msoft-float
        PRIVATE -mno-mmx
        PRIVATE -mno-sse
        PRIVATE -mno-sse2
        PRIVATE -mno-red-zone
        PRIVATE -mcmodel=kernel
    )
endif()