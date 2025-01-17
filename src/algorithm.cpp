#include "algorithm.h"

#include <iostream>
#include <cmath>

std::string demodulate(int M, const std::string& bin_preamb, const std::string& path) {
    if (M < 2 || (M & (M - 1)) != 0) {
        std::cerr << "Error: Порядок модуляции M должен быть степенью двойки и не меньше 2!" << std::endl;
        std::exit(1);
    }

    if (bin_preamb.size() % (int)std::log2(M) != 0) {
        std::cerr << "Error: Ошибка данных преамбулы!" << std::endl;
        std::exit(1);
    }

    std::vector<short> data = read_data(path);

    std::vector<std::complex<short>> iq = get_complex(data);

    std::vector<short> preamb = bin_to_short_preamb(bin_preamb, M);

    for (const auto& num: preamb) {
        if (num < 0 || num >= M) {
            std::cerr << "Error: Символ преамбулы выходит за пределы диапазона [0, " << (M - 1) << "]." << std::endl;
            std::exit(1);
        }
    }

    std::vector<std::complex<double>> iq_preamb = psk::modulate(preamb, M, M_PI / M);

    std::vector<std::complex<double>> ph_deltas = process_signal::calc_freq_offsets(iq, M);

    std::vector<std::complex<double>> iq_dedop = process_signal::remove_freq_offsets(iq, ph_deltas);

    std::vector<std::complex<double>> iq_cleared = process_signal::remove_init_phase(iq_dedop, iq_preamb);

    std::vector<short> demod_data = psk::demodulate(iq_cleared, M, M_PI / M);

    std::string demod_data_bin = dec_to_bin(demod_data, M);

    demod_data_bin = demod_data_bin.substr(std::log2(M) * preamb.size());

    return demod_data_bin;
}
