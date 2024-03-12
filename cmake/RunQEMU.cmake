set(QEMU_LOGFILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-log.txt)
set(QEMU_ARGUMENTS
    -cpu max
    -smp 1
    -m 512M
    -rtc base=localtime
    -serial stdio
    -boot order=d,menu=on,splash-time=100
    -enable-kvm
)

if(${PROJECT_NAME}_ARCHITECTURE STREQUAL x86_64)
    set(EDK2_OVMF_BINARY ${PARENT_PROJECT_ROOT}/external/ovmf/bin/RELEASEX64_OVMF.fd)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    list(APPEND QEMU_ARGUMENTS
        -no-reboot
        -no-shutdown
        -d int
        -D ${QEMU_LOGFILE}
        -S -s
    )
endif()

if(${PROJECT_NAME}_ARCHITECTURE STREQUAL x86_64)
    list(APPEND QEMU_ARGUMENTS
        -M q35
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        list(APPEND QEMU_ARGUMENTS -M smm=off)
    endif()
endif()

list(APPEND QEMU_ARGUMENTS
    -cdrom ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso
    -bios ${EDK2_OVMF_BINARY}
)

find_program(QEMU qemu-system-${${PROJECT_NAME}_ARCHITECTURE})

if(QEMU)
    add_custom_target(qemu-run-uefi ALL
        COMMAND qemu-system-${${PROJECT_NAME}_ARCHITECTURE} ${QEMU_ARGUMENTS}
        DEPENDS build-iso
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Running QEMU..."
    )
endif()