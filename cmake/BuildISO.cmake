find_program(XORRISO xorriso REQUIRED)

set(ISO_DIRECTORY ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-iso)
set(XORRISO_FLAGS -as mkisofs)

if(${PROJECT_NAME}_ARCHITECTURE STREQUAL x86_64)
    list(APPEND XORRISO_FLAGS
        -b limine-bios-cd.bin
        -no-emul-boot
        -boot-load-size 4
        -boot-info-table
        --efi-boot limine-uefi-cd.bin
        -efi-boot-part
        --efi-boot-image
        --protective-msdos-label
    )
endif()

file(COPY ${PROJECT_SCRIPT_DIRECTORY}/limine.cfg DESTINATION ${PARENT_PROJECT_BINARY_DIR})

if(XORRISO)
    add_custom_target(build-iso ALL
        COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso
        COMMAND xorriso ${XORRISO_FLAGS} ${PARENT_PROJECT_BINARY_DIR} -o ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso
        COMMAND ${PROJECT_BINARY_DIR}/external/limine/limine bios-install ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso
        DEPENDS limine kernel
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Building ${PROJECT_NAME}-iso"
    )
endif()