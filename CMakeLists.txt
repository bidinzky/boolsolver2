cmake_minimum_required(VERSION 3.15)
project(boolparser)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(boolparser main.cpp AstType.h AstParse.cpp AstParse.h AstExecute.cpp AstExecute.h)
target_link_libraries(boolparser ${CURSES_LIBRARIES})