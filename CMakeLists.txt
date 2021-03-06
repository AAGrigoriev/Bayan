cmake_minimum_required(VERSION 3.10)

project(bayan)

set(CMAKE_CXX_STANDARD 17)
set(SRC_PATH "src")
set(H_PATH   "include")
set(W_LIB ${CMAKE_PROJECT_NAME}_lib)
set(EXEC_NAME ${CMAKE_PROJECT_NAME})

find_package( Boost COMPONENTS program_options REQUIRED )
#include_directories( ${Boost_INCLUDE_DIR} )

find_package(Threads)
#find_package(Doxygen COMPONENTS dot)

add_executable(${EXEC_NAME} ${SRC_PATH}/main.cpp)

# LIBRARY 
add_library(${W_LIB} 
                        ${SRC_PATH}/com_parser.cpp
                        ${SRC_PATH}/dir_parser.cpp
                        ${SRC_PATH}/filter.cpp
                        ${SRC_PATH}/mask.cpp
                        ${SRC_PATH}/file_wrapper.cpp
                        ${SRC_PATH}/file_dublicate_parser.cpp
        )

target_link_libraries(${W_LIB}      PRIVATE ${Boost_LIBRARIES})
target_include_directories(${W_LIB} PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(${W_LIB} PRIVATE ${H_PATH})

# PROJECT 
target_link_libraries(${EXEC_NAME}      PRIVATE ${W_LIB})
target_include_directories(${EXEC_NAME} PRIVATE ${H_PATH})