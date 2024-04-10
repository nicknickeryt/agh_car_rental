cmake_minimum_required(VERSION 3.24)

project(
    agh_car_rental
    VERSION 0.1
    LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG 0.8.0
)
FetchContent_GetProperties(yaml-cpp)

if(NOT yaml-cpp_POPULATED)
  message(STATUS "Fetching yaml-cpp...")
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()

include_directories( inc )

file ( GLOB SOURCES "./src/*.cpp" )
add_executable( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries(${PROJECT_NAME} yaml-cpp::yaml-cpp)