cmake_minimum_required(VERSION 2.8)
project(libsocket)

FILE(GLOB SOURCE_FILES
src/serialization/*.cc
src/server/*.cc
src/socket/*.cc
src/core/*.cc
src/client/*.cc
)

include_directories(
include
external-deps/mystl/include
)

set(CMAKE_CXX_COMPILER g++)


add_library(libsocket STATIC ${SOURCE_FILES})
target_link_libraries(libsocket mystl)
