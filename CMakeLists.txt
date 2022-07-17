# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("Binary_B-Tree")

set (CMAKE_CXX_STANDARD 17)
# Включите подпроекты.
add_subdirectory ("Binary_B-Tree")
