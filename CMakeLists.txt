cmake_minimum_required(VERSION 3.28)
project(HomeWork3New C)

set(CMAKE_C_STANDARD 11)

add_executable(HomeWork3New JerryBoreeMain.c
        Jerry.c
        Jerry.h
        HashTable.c
        HashTable.h
        MultiValueHashTable.c
        MultiValueHashTable.h
        LinkedList.c
        LinkedList.h
        KeyValuePair.c
        KeyValuePair.h
        Defs.h
)
target_link_libraries(HomeWork3New m)
