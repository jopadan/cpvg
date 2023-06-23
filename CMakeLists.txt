cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)
project(rw_progress_bar LANGUAGES C)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "rw_progress_bar - single-file header C/C++ [fread:fwrite]_progress_bar buffered block stdio functions supporting status progress bar")

include(GNUInstallDirs)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-march=native -O3)
add_compile_options(-D_FILE_OFFSET_BITS=64)
add_compile_options(-fdata-sections)
add_compile_options(-ffunction-sections)
add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Wpedantic)
add_link_options(-Wl,--gc-sections)
#add_link_options(-Wl,--print-gc-sections)
add_link_options(-Wl,-s)

# pogress executable
add_executable(cpbar cpbar.c progress.h) 
set_target_properties(cpbar PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

install(FILES progress.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

