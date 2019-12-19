cmake_minimum_required(VERSION 3.15)
project(boolparser)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/boolsolver_lib)
add_executable(boolparser main.cpp)
target_link_libraries(boolparser boolsolver_lib)