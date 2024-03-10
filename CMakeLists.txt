cmake_minimum_required(VERSION 3.12)

project(
    SandPileModel
    VERSION 1.0
    DESCRIPTION "Abelian Sandpile model for C++ course ITMO 1 semestr"
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(bin)