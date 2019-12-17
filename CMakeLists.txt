cmake_minimum_required(VERSION 3.15)
project(boolparser)

set(CMAKE_CXX_STANDARD 17)

add_executable(boolparser main.cpp AstType.h AstParse.cpp AstParse.h AstExecute.cpp AstExecute.h)
target_link_libraries(boolparser ${CMAKE_SOURCE_DIR}/libncurses.a)