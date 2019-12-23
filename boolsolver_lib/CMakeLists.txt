cmake_minimum_required(VERSION 3.15)
project(boolsolver_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(boolsolver_lib AstExecute.cpp AstExecute.h AstType.h AstParse.h AstParse.cpp AstOptimize.cpp AstOptimize.h)
target_include_directories(boolsolver_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests)