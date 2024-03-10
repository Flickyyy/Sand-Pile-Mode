#pragma once

#include <cstdint>
#include <utility>
#include "myvector.h"
#include "parser.h"

struct TsvPoint{
    int16_t x, y;
    uint64_t val;
};


using SandMap = Vec<Vec<uint64_t>>;
using VecPair = Vec<std::pair<uint16_t, uint16_t>>;

bool UpdateSandPile(SandMap& map);
SandMap LoadTSV(const char* tsv);
