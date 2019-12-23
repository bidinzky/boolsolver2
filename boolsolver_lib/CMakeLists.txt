cmake_minimum_required(VERSION 3.15)
project(boolsolver_lib)
set(CMAKE_CXX_STANDARD 17)

find_package(Git QUIET)
if(GIT_FOUND)
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/tests/Catch2/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(tests/Catch2)

#set(CATCH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/tests/Catch2)
#add_library(Catch2 IMPORTED INTERFACE)
#set_property(Catch2 PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${CATCH_INCLUDE_DIR}")

file(GLOB LIB_SRC
        "*.h"
        "*.cpp"
        )
file(GLOB TEST_SRC
        "tests/*.h"
        "tests/*.cpp"
        )

add_library(boolsolver_lib ${LIB_SRC} AstType.cpp)
add_executable(boolsolver_lib_test ${TEST_SRC})
target_include_directories(boolsolver_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(boolsolver_lib_test Catch2 boolsolver_lib)
#catch_discover_tests(boolsolver_lib_test)