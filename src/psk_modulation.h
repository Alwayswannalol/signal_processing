#ifndef PSK_MODULATION_H
#define PSK_MODULATION_H

#include <vector>
#include <complex>
#include <cmath>

namespace psk {
    short gray_code(short num);
    std::vector<std::complex<double>> modulate(const std::vector<short>& data, int M, double phase_shift);
    std::vector<short> demodulate(const std::vector<std::complex<double>>& data, int M, double phase_shift);
}

#endif // !PSK_MODULATION_H
