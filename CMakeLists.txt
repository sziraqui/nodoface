# dummy cmakelists to make intellisense work in CLion
cmake_minimum_required(VERSION 3.0)
project(nodoface)
find_package(OpenCV REQUIRED)
find_package(dlib REQUIRED)
find_library(OpenFace REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*/*.cpp")
file(GLOB MAIN_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
include_directories(
        node_modules/node-addon-api
        node_modules/node-addon-api/src
)
add_library(${PROJECT_NAME} ${SOURCE_FILES} ${MAIN_FILES})