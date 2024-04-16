kernel_sources = files('kmain.cpp')
kernel_include = [include_directories('include/')]
kernel_include += limine_subproject_include

clangtidy_files += kernel_sources

kernel_exec = executable(
    'kernel',
    kernel_sources,
    include_directories: [kernel_include, libc_include],
    link_with: [libc_library],
    install: false,
)
