cmake_minimum_required(VERSION 3.5)

project(BoidsApp)

add_executable(BoidsApp WIN32 winmain.cpp)
target_link_libraries(BoidsApp PUBLIC user32.lib gdi32.lib)
target_link_libraries(BoidsApp PRIVATE BoidsLib)