cmake_minimum_required(VERSION 3.0.2)

PROJECT("CustomId")
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Builds/$<CONFIG>/${CMAKE_VS_PLATFORM_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Builds/$<CONFIG>/${CMAKE_VS_PLATFORM_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Builds/$<CONFIG>/${CMAKE_VS_PLATFORM_NAME})

if(MSVC)   
  add_definitions(-DWIN32_LEAN_AND_MEAN)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif(MSVC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


FILE(GLOB_RECURSE CID_SRC "src/*.cpp" "src/*.h")

add_library(custom_id STATIC ${CID_SRC})


FILE(GLOB_RECURSE TEST_SRC "test/*.cpp" "test/*.h")

add_executable(test_id ${TEST_SRC})

target_link_libraries( test_id custom_id )