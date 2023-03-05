cmake_minimum_required (VERSION 3.25)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")

project ("verisim")
add_subdirectory ("verisim")
add_subdirectory ("vpi")