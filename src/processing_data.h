#ifndef PROCESSING_DATA_H
#define PROCESSING_DATA_H

#include <vector>
#include <string>
#include <complex>

std::vector<short> read_data(const std::string& path);
std::vector<std::complex<short>> get_complex(const std::vector<short>& data);
std::vector<short> bin_to_short_preamb(const std::string& bin_preamb, int M);
std::string dec_to_bin(const std::vector<short>& data, int M);

#endif // !PROCESSING_DATA_H
