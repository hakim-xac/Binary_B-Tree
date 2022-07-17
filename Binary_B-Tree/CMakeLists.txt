# CMakeList.txt: проект CMake для Binary_B-Tree; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Binary_B-Tree
"Binary_B-Tree.cpp"
"Binary_B-Tree.h"
"Interface.h"
"Interface.cpp"
"TaskExecution.h"
"TaskExecution.cpp"
"BinaryBTree.h"
"BinaryBTree.cpp"
"Node.h"
"Node.cpp"
"Enums.h"
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
