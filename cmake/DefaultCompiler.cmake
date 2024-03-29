include(${CMAKE_CURRENT_LIST_DIR}/CheckAndApplyFlags.cmake)

# These are warning/diagnostic settings that we want to apply on our projects
set(desired_common_warning_flags

    # Base Warnings
    -Wall
    -Wextra

    # Diagnostics
    -fdiagnostics-show-option
    -fcolor-diagnostics

    # Disabled Warnings
    -Wno-padded

    # Desired Warnings
    -Wmissing-include-dirs
    -Wduplicated-cond
    -Wnull-dereference
)

set(desired_cpp_warning_flags
    -Wold-style-cast
    -Wnon-virtual-dtor
    -Wctor-dtor-privacy
    -Woverloaded-virtual
    -Wnoexcept
    -Wstrict-null-sentinel
    -Wuseless-cast
    -Wzero-as-null-pointer-constant
    -Wextra-semi

    # Disabled Warnings
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-exit-time-destructors # causes warnings if you use static values
    -Wno-global-constructors # causes warnings if you use static values
    -Wno-covered-switch-default
)

set(desired_common_compiler_optimization_flags
    -ffunction-sections # Place each function in its own section (ELF Only)
    -fdata-sections # Place each data in its own section (ELF Only)
    -fdevirtualize # Attempt to convert calls to virtual functions to direct calls
)

# ###################################################
# Settings enforced when we're the primary project #
# ###################################################
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    apply_supported_compiler_flags_globally(C desired_common_warning_flags)
    apply_supported_compiler_flags_globally(CXX desired_common_warning_flags)
    apply_supported_compiler_flags_globally(CXX desired_cpp_warning_flags)
    apply_supported_compiler_flags_globally(C desired_common_compiler_optimization_flags)
    apply_supported_compiler_flags_globally(CXX desired_common_compiler_optimization_flags)
endif()

# ###################################
# Settings enforced no matter what #
# ###################################
apply_supported_compiler_flags_globally(C "-Wno-unknown-pragmas")
apply_supported_compiler_flags_globally(CXX "-Wno-unknown-pragmas")