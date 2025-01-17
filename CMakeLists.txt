cmake_minimum_required(VERSION 3.10)

project(signal_processing)

add_executable(process main.cpp src/psk_modulation.cpp src/processing_data.cpp src/signal_processing.cpp src/algorithm.cpp)
