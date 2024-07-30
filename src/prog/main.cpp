#include <iostream>

#include <ctime>

#include "audiorw.hpp"

int main(int argc, char **argv) {
    int output_sample_rate = 0;
    int output_channels = 0;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input file> <output file> [-ar sample_rate] [-ac channels]\n",
                argv[0]);
        return -1;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    // Parse command line options
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "-ar") == 0 && i + 1 < argc) {
            output_sample_rate = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-ac") == 0 && i + 1 < argc) {
            output_channels = atoi(argv[++i]);
        }
    }

    clock_t start_time = clock();

    try {
        double sample_rate;
        auto audio = audiorw::read(argv[1], sample_rate);
        audiorw::write(audio, argv[2], sample_rate, output_sample_rate);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    clock_t end_time = clock();
    double timeout = (double) (end_time - start_time) / CLOCKS_PER_SEC * 1000;
    printf("Timeout: %f ms\n", timeout);
    return 0;
}