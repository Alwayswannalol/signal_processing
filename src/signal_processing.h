#ifndef SIGNAL_PROCESSING_H
#define SIGNAL_PROCESSING_H

#include <vector>
#include <complex>

namespace process_signal {
    std::vector<std::complex<double>> calc_freq_offsets(const std::vector<std::complex<short>>& data, int M);
    std::vector<std::complex<double>> remove_freq_offsets(const std::vector<std::complex<short>>& data, const std::vector<std::complex<double>>& ph_deltas);
    std::vector<std::complex<double>> remove_init_phase(const std::vector<std::complex<double>>& data, const std::vector<std::complex<double>>& preamb);
}

#endif // !SIGNAL_PROCESSING_H
