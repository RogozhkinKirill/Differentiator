cmake_minimum_required(VERSION 3.9)
project(Diff)

set(CMAKE_CXX_STANDARD 17)

add_executable(Differentiator main.cpp
        TreeLib/Node.cpp
        TreeLib/Tree.cpp
        TreeLib/TreeLib.h

        decoder/decoder.cpp
        decoder/decoder.h

        Differentiator/Differentiator.cpp
        Differentiator/Differentiator.h RecursiveDescentParser/RDP.cpp RecursiveDescentParser/RDP.h)