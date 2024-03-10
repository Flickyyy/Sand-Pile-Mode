#pragma once
#include <fstream>
#include <cstdint>
#include <cassert>
#include "myvector.h"
#include "sandpile.h"

//MEME: https://www.youtube.com/shorts/7fqg6KGBeyU

void WriteToBmp(const SandMap& pixels, const char* file_name);
