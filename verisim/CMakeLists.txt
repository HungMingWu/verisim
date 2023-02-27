add_executable(verisim verisim.cpp vpi_modules.cpp vpi_priv.cpp)
set_target_properties(verisim PROPERTIES CXX_STANDARD 20)
target_link_libraries(verisim PRIVATE $<$<PLATFORM_ID:Linux>:dl>)