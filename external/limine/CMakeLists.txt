project(Limine-bootloader
    LANGUAGES C
)

add_executable(limine limine/limine.c)

target_compile_options(limine PRIVATE
    -std=c99
)

file(COPY_FILE limine/limine.h ${PARENT_PROJECT_ROOT}/src/kernel/include/limine.h ONLY_IF_DIFFERENT)

set(LIMINE_EXECUTABLE_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/limine/limine-uefi-cd.bin
)

if(${PARENT_PROJECT_NAME}_ARCHITECTURE STREQUAL x86_64)
    list(APPEND LIMINE_EXECUTABLE_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/limine/limine-bios.sys
        ${CMAKE_CURRENT_SOURCE_DIR}/limine/limine-bios-cd.bin
        ${CMAKE_CURRENT_SOURCE_DIR}/limine/BOOTX64.EFI
        ${CMAKE_CURRENT_SOURCE_DIR}/limine/BOOTIA32.EFI
    )
endif()