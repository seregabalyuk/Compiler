set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(PROJECT_INCLUDES ${CMAKE_SOURCE_DIR}/src)
# add_compile_options(-fconcepts-diagnostics-depth=2)

project(Compiler)

add_executable(main src/main.cpp)
target_include_directories(main PRIVATE ${PROJECT_INCLUDES})
