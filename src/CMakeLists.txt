project(ava-kernel
    VERSION ${PARENT_PROJECT_VERSION}
    DESCRIPTION "Project-ava kernel"
    LANGUAGES CXX C ASM
)

add_subdirectory(klibc)
add_subdirectory(kernel)