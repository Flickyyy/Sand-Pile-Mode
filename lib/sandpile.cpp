
#include "sandpile.h"
#include <cassert>
#include <fstream>
#include <iostream>


bool UpdateSandPile(SandMap& map) {
    VecPair drops_indexes;
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    for (uint16_t i = 0; i < map.size(); ++i) {
        for (uint16_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] >= 4) {
                if (i == 0) {
                    up = true;
                }
                if (i + 1 == map.size()) {
                    down = true;
                }
                if (j == 0) {
                    left = true;
                }
                if (j + 1 == map[i].size()) {
                    right = true;
                }
                drops_indexes.push_back({i, j});
            }
        }
    }

    if (up) {
        map = reversed(map);
        map.push_back(Vec<uint64_t>(map[0].size(), 0));
        map = reversed(map);
    }
    if (down) {
        map.push_back(Vec<uint64_t>(map[0].size(), 0));
    }
    if (left) {
        for (uint16_t i = 0; i < map.size(); ++i) {
            map[i] = reversed(map[i]);
            map[i].push_back(0);
            map[i] = reversed(map[i]);
        }
    }
    if (right) {
        for (uint16_t i = 0; i < map.size(); ++i) {
            map[i].push_back(0);
        }
    }


    uint16_t i_sht = up;
    uint16_t j_sht = left;
    for (auto[i, j] : drops_indexes) {
        map[i + i_sht][j + j_sht] -= 4;
        map[i + i_sht + 1][j + j_sht] += 1;
        map[i + i_sht - 1][j + j_sht] += 1;
        map[i + i_sht][j + j_sht + 1] += 1;
        map[i + i_sht][j + j_sht - 1] += 1;
    }

    return !drops_indexes.empty();
}

SandMap LoadTSV(const char* tsv) {
    assert(tsv != nullptr);
    Vec<TsvPoint> points;
    std::ifstream ifs(tsv);
    if (!ifs.is_open()) {
        std::cerr << "Can't open " << tsv << " tsv file\n";
        exit(1);
    }

    int16_t x, y;
    int16_t max_x = INT16_MIN, min_x = INT16_MAX, max_y = INT16_MIN, min_y = INT16_MAX;
    uint64_t val;
    while (ifs >> x >> y >> val) {
        points.push_back({x, y, val});
        max_x = std::max(max_x, x);
        min_x = std::min(min_x, x);
        max_y = std::max(max_y, y);
        min_y = std::min(min_y, y);
    }
    SandMap map(max_y - min_y + 1, Vec<uint64_t>(max_x - min_x + 1));
    for (auto[x, y, val] : points) {
        map[1 * y - min_y][1 * x - min_x] = val;
    }

    return map;
}
