#include <iostream>
#include <unistd.h>

#include "src/algorithm.h"

int main(int argc, char* argv[]) {
    // test: -m 4 -p 01011110 -f ../data.bin
    int opt;
    std::string path;
    short M;
    std::string bin_preamb;

     while ((opt = getopt(argc, argv, "m:p:f:")) != -1) {
        switch (opt) {
            case 'm':
                M = std::stoi(optarg);
                break;
            case 'p':
                bin_preamb = optarg;
                break;
            case 'f':
                path = optarg;
                break;
            default:
                std::cerr << "Error: Ошибка в использовании!\nИспользование: " << argv[0] << " -m <modulation_order> -p <preamble> -f <file>\n";
                return 1;
        }
    }

    if (M == 0 || bin_preamb.empty() || path.empty()) {
        std::cerr << "Error: Ошибка в использовании!\nИспользование: " << argv[0] << " -m <modulation_order> -p <preamble> -f <file>\n";
        return 1;
    }

    std::string result = demodulate(M, bin_preamb, path);

    std::cout << result << std::endl;

    return 0;
}
