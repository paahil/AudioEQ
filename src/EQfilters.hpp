#ifndef EQ_FILTERSHPP
#define EQ_FILTERSHPP
#include <iostream>
#include <vector>
namespace EQ {
std::vector<double> LowShelf(std::vector<double> input, double dB,
                             double cofreq);

std::vector<double> HighShelf(std::vector<double> input, double dB,
                              double cofreq);
}  // namespace EQ

#endif