include(FetchContent)
FetchContent_Declare(lexy URL https://lexy.foonathan.net/download/lexy-src.zip)
FetchContent_MakeAvailable(lexy)

add_executable(verisim verisim.cpp vpi_modules.cpp vpi_priv.cpp)
set_target_properties(verisim PROPERTIES CXX_STANDARD 20)
target_link_libraries(verisim 
PRIVATE 
	foonathan::lexy
	$<$<PLATFORM_ID:Linux>:dl>
)