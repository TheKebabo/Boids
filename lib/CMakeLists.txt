cmake_minimum_required(VERSION 3.5)

project(BoidsLib)

file(GLOB lib_src "src/*.cpp")
add_library(BoidsLib ${lib_src})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)