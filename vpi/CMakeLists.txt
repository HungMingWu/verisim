add_library(vpi)

target_sources(vpi
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    mt19937int.cpp
    stringheap.cpp
    sys_convert.cpp
    sys_countdrivers.cpp
    sys_darray.cpp
    sys_deposit.cpp
    sys_display.cpp
    sys_fileio.cpp
    sys_finish.cpp
    sys_plusargs.cpp
    sys_priv.cpp
    sys_queue.cpp
    sys_random.cpp
    sys_random_mti.cpp
    sys_readmem.cpp
    sys_readmem_lex.cpp
    sys_scanf.cpp
    sys_table.cpp
    sys_time.cpp
    sys_vcd.cpp
    sys_vcdoff.cpp
    vcd_priv.cpp
    vpi_priv.cpp
    vpi_tasks.cpp
    FILE_SET cxx_modules1 TYPE CXX_MODULE_HEADER_UNITS FILES
    wrapper.cpp
)

set_target_properties(vpi PROPERTIES CXX_STANDARD 20)
target_include_directories(vpi PRIVATE ../common)