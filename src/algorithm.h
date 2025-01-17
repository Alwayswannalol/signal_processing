#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>

#include "processing_data.h"
#include "psk_modulation.h"
#include "signal_processing.h"

std::string demodulate(int M, const std::string& bin_preamb, const std::string& path);

#endif // !ALGORITHM_H
