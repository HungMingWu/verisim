add_library(vpi)

target_sources(vpi
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    sys_convert.cpp
    vpi_priv.cpp
    vpi_tasks.cpp
    FILE_SET cxx_modules1 TYPE CXX_MODULE_HEADER_UNITS FILES
    wrapper.cpp
 )

set_target_properties(vpi PROPERTIES CXX_STANDARD 20)
target_include_directories(vpi PRIVATE ../common)