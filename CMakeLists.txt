cmake_minimum_required(VERSION 3.10)
project(Duplicate-File-Remover)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/class.cpp
    src/class.h
)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)