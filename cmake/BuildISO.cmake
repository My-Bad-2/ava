find_program(XORRISO xorriso)

set(ISO_DIRECTORY ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-iso)
set(XORRISO_FLAGS -as mkisofs)

if(KERNEL_ARCHITECTURE STREQUAL x86_64)
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

if(${PROJECT_NAME}_ARCHITECTURE STREQUAL x86_64)
    add_custom_target(copy-iso-files ALL
        COMMAND rm -rf ${ISO_DIRECTORY}
        COMMAND mkdir -p ${ISO_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy external/limine/limine/limine-uefi-cd.bin ${ISO_DIRECTORY}/limine-uefi-cd.bin
        COMMAND ${CMAKE_COMMAND} -E copy external/limine/limine/limine-bios.sys ${ISO_DIRECTORY}/limine-bios.sys
        COMMAND ${CMAKE_COMMAND} -E copy external/limine/limine/limine-bios-cd.bin ${ISO_DIRECTORY}/limine-bios-cd.bin
        COMMAND ${CMAKE_COMMAND} -E copy external/limine/limine/BOOTX64.EFI ${ISO_DIRECTORY}/BOOTX64.EFI
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/src/kernel/kernel ${ISO_DIRECTORY}/kernel
        COMMAND ${CMAKE_COMMAND} -E copy scripts/limine.cfg ${ISO_DIRECTORY}/limine.cfg
        DEPENDS limine kernel
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Copying ${PROJECT_NAME}-iso files"
    )
endif()

if(XORRISO)
    add_custom_target(build-iso ALL
        COMMAND xorriso ${XORRISO_FLAGS} ${ISO_DIRECTORY} -o ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso
        COMMAND ${PROJECT_BINARY_DIR}/external/limine/limine bios-install ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso
        COMMAND rm -rf ${ISO_DIRECTORY}
        DEPENDS copy-iso-files
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Building ${PROJECT_NAME}-iso"
    )
endif()