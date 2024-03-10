
#include "parser.h"
#include <iostream>
#include <algorithm>

Arguments Parse(const int argc, const char **argv) {
    const char* kFreqArg      = "--freq=";
    const char* kMaxIterArg   = "--max-iter=";
    const char* kInputArg     = "--input=";
    const char* kOutputArg    = "--output=";

    Arguments args;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            args.freq = atoll(argv[++i]);
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            args.max_iter = atoll(argv[++i]);
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            strcpy(args.input, argv[++i]);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            strcpy(args.output, argv[++i]);
        } else if (strncmp(argv[i], kFreqArg, strlen(kFreqArg)) == 0) {
            args.freq  = atoll(argv[i] + strlen(kFreqArg));
        } else if (strncmp(argv[i], kMaxIterArg, strlen(kMaxIterArg)) == 0) {
            args.max_iter = atoll(argv[i] + strlen(kMaxIterArg));
        } else if (strncmp(argv[i], kInputArg, strlen(kInputArg)) == 0) {
            strcpy(args.input, argv[i] + strlen(kInputArg));
        } else if (strncmp(argv[i], kOutputArg, strlen(kOutputArg)) == 0) {
            strcpy(args.output, argv[i] + strlen(kOutputArg));
        } else {
            std::cerr << argv[i] << " is incorrect args" << '\n';
            exit(1);
        }
    }

    return args;
}
