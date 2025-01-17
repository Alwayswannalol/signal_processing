#include "processing_data.h"

#include <fstream>
#include <bitset>
#include <iostream>

std::vector<short> read_data(const std::string& path) {
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Ошибка открытия файла!" << std::endl;
        std::exit(1);
    }

    std::vector<short> nums;
    short num;
    while (file.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        nums.push_back(num);
    }
    return nums;
}

std::vector<std::complex<short>> get_complex(const std::vector<short>& data) {
    if (data.size() % 2 != 0) {
        std::cerr << "Error: Нечетное количество данных!" << std::endl;
        std::exit(1);
    } 

    std::vector<std::complex<short>> complex_nums;
    for (int i = 1; i <= data.size(); i += 2) {
        complex_nums.push_back(std::complex<short>(data[i - 1], data[i]));
    }
    return complex_nums;
}

std::vector<short> bin_to_short_preamb(const std::string& bin_preamb, int M) {
    std::vector<short> converted_preamb;
    int num_bits = std::log2(M);
    for (int i = 0; i < bin_preamb.size(); i += num_bits) {
        std::string bin_num = bin_preamb.substr(i, num_bits);
        converted_preamb.push_back(std::stoi(bin_num, nullptr, 2));
    }
    return converted_preamb;
}

std::string dec_to_bin(const std::vector<short>& data, int M) {
    std::string res = "";
    int len = std::log2(M);
    for (const auto& num: data) {
        std::bitset<16> b(num);
        std::string b_str = b.to_string();
        res += b_str.substr(b_str.length() - len, len);
    }
    return res;
}
