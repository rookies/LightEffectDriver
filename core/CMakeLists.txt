cmake_minimum_required(VERSION 3.10)
project(core)

set(CMAKE_CXX_STANDARD 11)

add_library(LightEffectDriverCore Core.cc Core.hh Effect.hh Order.hh Direction.hh Curve.hh Curve.cc)