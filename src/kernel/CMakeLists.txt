file(GLOB KMAIN_DIRECTORY_SOURCES "*.c")

file(GLOB_RECURSE ARCH_DIRECTORY_SOURCES
    "arch/${${PARENT_PROJECT_NAME}_ARCHITECTURE}/*.c"
    "arch/${${PARENT_PROJECT_NAME}_ARCHITECTURE}/*.cpp"
)

set(KERNEL_SOURCE_FILES ${KMAIN_DIRECTORY_SOURCES} ${ARCH_DIRECTORY_SOURCES})

add_executable(kernel ${KERNEL_SOURCE_FILES})

target_link_libraries(kernel PRIVATE klibc)

target_include_directories(kernel
    PRIVATE include
    PRIVATE include/arch/${${PARENT_PROJECT_NAME}_ARCHITECTURE}
)

set_target_properties(kernel PROPERTIES
    OUTPUT_NAME kernel.elf
    RUNTIME_OUTPUT_DIRECTORY ${PARENT_PROJECT_BINARY_DIR}
)

target_compile_options(kernel
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
    target_compile_options(kernel
        PRIVATE -march=x86-64
        PRIVATE -msoft-float
        PRIVATE -mno-mmx
        PRIVATE -mno-sse
        PRIVATE -mno-sse2
        PRIVATE -mno-red-zone
        PRIVATE -mcmodel=kernel
    )

    target_link_options(kernel
        PRIVATE -T ${CMAKE_CURRENT_LIST_DIR}/linker/x86-64-link.ld
        PRIVATE -m elf_x86_64
    )
endif()

target_link_options(kernel
    PRIVATE -z max-page-size=0x1000
    PRIVATE -nostdlib
    PRIVATE -static
    PRIVATE --no-dynamic-linker
)