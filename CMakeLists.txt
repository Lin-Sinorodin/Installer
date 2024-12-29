cmake_minimum_required(VERSION 3.30)
project(lin_installer)

set(CMAKE_CXX_STANDARD 17)

add_executable(lin_installer main.cpp
        file.cpp
        file.h
        directory.cpp
        directory.h
        installer.cpp
        installer.h
)
