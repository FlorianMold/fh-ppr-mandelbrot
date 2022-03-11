cmake_minimum_required(VERSION 3.21)
project(fh_ppr_mandelbrot)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(fh_ppr_mandelbrot main.cpp tga.cpp tga.h)
