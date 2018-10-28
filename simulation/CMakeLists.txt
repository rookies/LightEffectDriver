cmake_minimum_required(VERSION 3.10)
project(simulation)

set(CMAKE_CXX_STANDARD 11)

add_executable(simulation main.cc Simulation.cc Simulation.hh Light.cc Light.hh)
target_link_libraries(simulation sfml-graphics)
target_link_libraries(simulation sfml-window)
target_link_libraries(simulation sfml-system)
target_link_libraries(simulation ${CMAKE_SOURCE_DIR}/../core/cmake-build-debug/libLightEffectDriverCore.a)
target_include_directories(simulation PRIVATE ${CMAKE_SOURCE_DIR}/../core/)