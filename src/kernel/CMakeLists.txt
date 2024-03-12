project(ava-kernel
    VERSION ${PARENT_PROJECT_VERSION}
    DESCRIPTION "Project-ava kernel"
    LANGUAGES CXX C
)

file(GLOB KMAIN_DIRECTORY_SOURCES "*.c")

file(GLOB_RECURSE ARCH_DIRECTORY_SOURCES
    "arch/${${PARENT_PROJECT_NAME}_ARCHITECTURE}/*.c"
    "arch/${${PARENT_PROJECT_NAME}_ARCHITECTURE}/*.cpp"
)

set(KERNEL_SOURCE_FILES ${KMAIN_DIRECTORY_SOURCES} ${ARCH_DIRECTORY_SOURCES})

add_executable(kernel ${KERNEL_SOURCE_FILES})

target_include_directories(kernel
    PRIVATE include
    PRIVATE include/arch/${${PARENT_PROJECT_NAME}_ARCHITECTURE}
)

set_target_properties(kernel PROPERTIES
    OUTPUT_NAME kernel.elf
    RUNTIME_OUTPUT_DIRECTORY ${PARENT_PROJECT_BINARY_DIR}
)

target_compile_options(kernel PRIVATE -Werror
    -ffreestanding
    -nostdlib
    -fno-omit-frame-pointer
    -fno-stack-protector
    -fno-pic
    -fno-pie
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<C_COMPILER_ID:Clang>:-target x86_64-pc-elf>
)

if(${PARENT_PROJECT_NAME}_ARCHITECTURE)
    target_compile_options(kernel PRIVATE
        -march=x86-64
        -msoft-float
        -mno-mmx
        -mno-sse
        -mno-sse2
        -mno-red-zone
        -mcmodel=kernel
    )

    target_link_options(kernel PRIVATE
        -T ${CMAKE_CURRENT_LIST_DIR}/linker/x86-64-link.ld
        -m elf_x86_64
    )
endif()

target_link_options(kernel PRIVATE
    -z max-page-size=0x1000
    -nostdlib
    -static
    --no-dynamic-linker
)

target_link_libraries(kernel PRIVATE klibc)