set(QEMU_LOGFILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-log.txt)
set(QEMU_ARGUMENTS
    -cpu max -smp 1 -m 512M
    -rtc base=localtime -serial stdio
    -boot order=d,menu=on,splash-time=100
    -accel kvm
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    list(APPEND QEMU_ARGUMENTS
        -no-reboot -no-shutdown
        -d int -D ${QEMU_LOGFILE}
        -S -s
    )
endif()

if(${PROJECT_NAME}_ARCHITECTURE STREQUAL x86_64)
    list(APPEND QEMU_ARGUMENTS
        -M q35 -bios ${CMAKE_CURRENT_LIST_DIR}/external/ovmf/bin/RELEASEX64_OVMF.fd
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        list(APPEND QEMU_ARGUMENTS -M smm=off)
    endif()
endif()

find_program(QEMU qemu-system-${${PROJECT_NAME}_ARCHITECTURE})

if(QEMU)
    add_custom_target(qemu-run-uefi ALL
        COMMAND qemu-system-${${PROJECT_NAME}_ARCHITECTURE} ${QEMU_ARGUMENTS} -cdrom ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.iso
        DEPENDS build-iso
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMENT "Running QEMU..."
    )
endif()