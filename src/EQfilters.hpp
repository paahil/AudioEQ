#ifndef EQ_FILTERSHPP
#define EQ_FILTERSHPP
#include <iostream>

std::vector<double> LowShelf(std::vector<double> input, double dB);

std::vector<double> HighShelf(std::vector<double> input, double dB);

#endif