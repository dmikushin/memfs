cmake_minimum_required(VERSION 3.10)

project(memfs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE3 REQUIRED fuse3)

add_subdirectory(ThirdParty/memory)

add_library(${PROJECT_NAME} STATIC src/${PROJECT_NAME}.cpp src/Fuse.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ThirdParty/magic_enum/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${FUSE3_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE FUSE_USE_VERSION=30 __CYGWIN__)
target_link_libraries(${PROJECT_NAME} ${FUSE3_LIBRARIES} foonathan_memory)

add_executable(test_${PROJECT_NAME} src/test/test_${PROJECT_NAME}.cpp)
target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME})

