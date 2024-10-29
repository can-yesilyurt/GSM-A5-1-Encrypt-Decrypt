cmake_minimum_required(VERSION 3.10)

project(encrypt_GSM_A5-1)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(encrypt_GSM_A5-1 encrypt_GSM_A5-1.cpp)

install(TARGETS encrypt_GSM_A5-1 DESTINATION /usr/local/bin)
