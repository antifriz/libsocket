cmake_minimum_required(VERSION 2.8)
project(libInetWrappersCxx)

FILE(GLOB SOURCE_FILES
src/serialization/*.cc
src/server/*.cc
src/socket/*.cc
src/core/*.cc
)

include_directories(
include
../mystl/include
)

set(CMAKE_CXX_COMPILER g++)


add_library(InetWrappersCxx STATIC ${SOURCE_FILES})
target_link_libraries(InetWrappersCxx mystl)
