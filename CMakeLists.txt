cmake_minimum_required(VERSION 3.10)
project(memfs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE3 REQUIRED fuse3)

add_executable(memfs src/memfs.cpp)
target_include_directories(memfs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(memfs PRIVATE ${FUSE3_INCLUDE_DIRS})
target_compile_definitions(memfs PRIVATE FUSE_USE_VERSION=30 __CYGWIN__)
target_link_libraries(memfs ${FUSE3_LIBRARIES})
