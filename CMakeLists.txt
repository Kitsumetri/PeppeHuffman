cmake_minimum_required(VERSION 3.22)
project(PeppeHuffman)

set(CMAKE_CXX_STANDARD 23)

add_executable(PeppeHuffman main.cpp
        PriorityQueue.cpp PriorityQueue.h
        H_Node.cpp H_Node.h
        H_tree.cpp H_tree.h
        Compress_Decompress.cpp Compress_Decompress.h
        Words.cpp Words.h)
