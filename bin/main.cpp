#include <lib/bmp_writer.h>
#include <lib/sandpile.h>
#include <lib/myvector.h>
#include <lib/parser.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <fstream>

int main(int argc, const char** argv) {
    Arguments args = Parse(argc, argv);
    SandMap map = LoadTSV(args.input);
    uint64_t iteration = 0;
    char buffer[1024];

    if (!std::filesystem::exists(args.output) && !std::filesystem::create_directory(args.output)) {
        std::cerr << "Can't create directory: " << args.output << '\n';
        exit(1);
    }

    while(UpdateSandPile(map) && iteration < args.max_iter) {
        iteration += 1;
        if (args.freq != 0 && iteration % args.freq == 0) {
            sprintf(buffer, "%s", args.output);
            sprintf(buffer + strlen(buffer), "my%d.bmp", iteration);
            WriteToBmp(map, buffer);
        }
    }

    //Last iteration writing if needed
    sprintf(buffer, "%s", args.output);
    sprintf(buffer + strlen(buffer), "my%d.bmp", iteration);
    WriteToBmp(map, buffer);

    return 0;
}
