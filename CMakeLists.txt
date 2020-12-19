cmake_minimum_required(VERSION 3.16)
project(serial_yaml_catch2)

set(CMAKE_CXX_STANDARD 20)

add_executable(serial_yaml_catch2 main.cpp)

target_include_directories(serial_yaml_catch2 PRIVATE .)

find_package(yaml-cpp REQUIRED)
target_link_libraries(serial_yaml_catch2 PRIVATE yaml-cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(libyaml REQUIRED IMPORTED_TARGET yaml-0.1)
target_link_libraries(serial_yaml_catch2 PRIVATE PkgConfig::libyaml)

pkg_check_modules(libfyaml REQUIRED IMPORTED_TARGET libfyaml)
target_link_libraries(serial_yaml_catch2 PRIVATE PkgConfig::libfyaml)

find_package(catch2 REQUIRED)
target_link_libraries(serial_yaml_catch2 PRIVATE catch2)