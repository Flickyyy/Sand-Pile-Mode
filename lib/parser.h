#pragma once
#include <cstring>
#include <cstdint>

struct Arguments {
    Arguments() {
        strcpy(input, "");
        strcpy(output, "images/");
    }
    char input[1024];
    char output[1024];
    std::size_t max_iter = SIZE_MAX;
    std::size_t freq = 0;
};

Arguments Parse(const int argc, const char **argv);
