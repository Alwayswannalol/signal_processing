#include "signal_processing.h"

namespace process_signal {
    std::vector<std::complex<double>> calc_freq_offsets(const std::vector<std::complex<short>>& data, int M) {
        std::vector<std::complex<double>> freq_offsets;
        for (int i = 1; i < data.size(); i++) {
            std::complex<double> cur = std::complex<double>(static_cast<double>(data[i].real()), static_cast<double>(data[i].imag()));
            std::complex<double> prev = std::complex<double>(static_cast<double>(data[i - 1].real()), static_cast<double>(data[i - 1].imag()));
            std::complex<double> num = std::pow(std::pow(cur, M) * std::conj(std::pow(prev, M)), 1.0 / M);
            freq_offsets.push_back(num);
        }

        return freq_offsets;
    }

    std::vector<std::complex<double>> remove_freq_offsets(const std::vector<std::complex<short>>& data, const std::vector<std::complex<double>>& ph_deltas) {
        std::vector<double> ph_acc{0};
        for (int i = 0; i < ph_deltas.size(); i++) {
            double arg_delt = std::arg(ph_deltas[i]);
            ph_acc.push_back(ph_acc[i] + arg_delt);
        }
        std::vector<std::complex<double>> data_dedop;
        std::complex<double> exp_compl(0, -1);
        for (int i = 0; i < data.size(); i++) {
            std::complex<double> cur = std::complex<double>(static_cast<double>(data[i].real()), static_cast<double>(data[i].imag()));
            data_dedop.push_back(cur * (std::exp(exp_compl * ph_acc[i])));
        }
        return data_dedop;
    }

    std::vector<std::complex<double>> remove_init_phase(const std::vector<std::complex<double>>& data, const std::vector<std::complex<double>>& preamb) {
        std::complex<double> init_phase = 0;
        double sum_denom = 0;
        for (int i = 0; i < preamb.size(); i++) {
            init_phase += data[i] * std::conj(preamb[i]);
            sum_denom += std::abs(data[i]);
        }
        init_phase = init_phase / sum_denom;
        std::vector<std::complex<double>> data_cleared;
        for (int i = 0; i < data.size(); i++) {
            data_cleared.push_back(data[i] * std::conj(init_phase));
        }
        return data_cleared;
    }
}
