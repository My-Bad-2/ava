# Module Configuration
doxygen_project_name = get_variable(
    'doxygen_project_name',
    meson.project_name(),
)
doxygen_version = get_variable('doxygen_version', meson.project_version())
doxygen_description = get_variable('doxygen_description', '')
doxygen_output_dir = get_variable(
    'doxygen_output_dir',
    meson.project_build_root() / 'docs',
)

doxygen_input = get_variable(
    'doxygen_input',
    [
        meson.project_source_root() / 'src',
        meson.project_source_root() / 'src/kernel',
        meson.project_source_root() / 'src/libc',
        meson.project_source_root() / 'README.md',
    ],
)

doxygen_input_additional = get_variable('doxygen_input_additional', [])

doxygen_input_parsed = ''
foreach item : doxygen_input + doxygen_input_additional
    doxygen_input_parsed += item + ' '
endforeach

doxygen_excludes = get_variable('doxygen_excludes', '')
doxygen_mainpage_md = get_variable(
    'doxygen_mainpage_md',
    meson.project_source_root() / 'README.md',
)

doxygen_template_path = meson.project_source_root() / 'docs/template'
doxygen_html_path = meson.project_source_root() / 'docs/defaults'

# Populate Configuration Values
doxyfile_config_data = {
    'PROJECT_NAME': doxygen_project_name,
    'PROJECT_VERSION': doxygen_version,
    'PROJECT_DESCRIPTION': doxygen_description,
    'OUTPUT_DIR': doxygen_output_dir,
    'INPUT_DIR': doxygen_input_parsed,
    'EXCLUDE_PATTERNS': doxygen_excludes,
    'MD_AS_MAINPAGE': doxygen_mainpage_md,
    'DOXYGEN_TEMPLATE_PATH': doxygen_template_path,
    'HTML_HEADER': doxygen_html_path,
}

doxyfile_config = configuration_data()
foreach var, value : doxyfile_config_data
    doxyfile_config.set(var, value)
endforeach

doxyfile_input = get_variable('doxyfile_input', files('Doxyfile.in'))
doxyfile = get_variable(
    'doxyfile',
    configure_file(
        input: doxyfile_input,
        output: 'Doxyfile',
        configuration: doxyfile_config_data,
    ),
)

# Doxygen Build Target
doxygen = find_program('doxygen', required: false, disabler: true)
run_target('docs', command: [doxygen, doxyfile])
