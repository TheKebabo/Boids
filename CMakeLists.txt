cmake_minimum_required(VERSION 3.5)
project(BoidsProj VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(lib)     # look in lib subdirectory for CMakeLists.txt to process
add_subdirectory(app)    # look in apps subdirectory for CMakeLists.txt to process