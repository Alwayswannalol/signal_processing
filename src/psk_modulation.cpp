#include "psk_modulation.h"

namespace psk {
    short gray_code(short num) {
        return num ^ (num >> 1);
    }

    std::vector<std::complex<double>> modulate(const std::vector<short>& data, int M, double phase_shift) {
        std::vector<double> phases;
        for (int i = 0; i < M; i++) {
            phases.push_back(2 * M_PI * i / M);
        }
        std::vector<std::complex<double>> modulated_signal;
        for (int i = 0; i < data.size(); i++) {
            short gray_num = gray_code(data[i]);
            double phase = phases[gray_num] + phase_shift;
            modulated_signal.push_back(std::exp(std::complex<double>(0, phase)));
        }
        return modulated_signal;
    }

    std::vector<short> demodulate(const std::vector<std::complex<double>>& data, int M, double phase_shift) {
        std::vector<short> demod_data;
        double angle_step = 2 * M_PI / M;
        for (const auto& sample : data) {
            double phase = std::arg(sample);
            phase -= phase_shift;
            if (phase < 0) {
                phase += 2 * M_PI;
            }
            int symbol = static_cast<int>(round(phase / angle_step)) % M;
            short gray_symbol = gray_code(symbol);
            demod_data.push_back(gray_symbol);
        }
        return demod_data;
    }
}
