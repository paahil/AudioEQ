#include "EQfilters.hpp"

#include <cmath>

#include "aquila.h"

namespace EQ {
void ChangeLowShelf(unsigned int index, double gaindB, double cofreq) {
  unsigned int FS = 44100;
  const double pi = 3.14159265358979323846;
  const double gain = std::pow(10, (gaindB / 20));
  const double angcofreq = (cofreq * 2 * pi) / FS;
  std::cout << "in Change Low";
  std::vector<double> num, den;
  num.push_back((gain * std::tan(angcofreq / 2) + std::sqrt(gain)) /
                (std::tan(angcofreq / 2) + std::sqrt(gain)));
  num.push_back((gain * std::tan(angcofreq / 2) - std::sqrt(gain)) /
                (std::tan(angcofreq / 2) + std::sqrt(gain)));
  den.push_back((std::tan(angcofreq / 2) - std::sqrt(gain)) /
                (std::tan(angcofreq / 2) + std::sqrt(gain)));
  if (index >= Controls.filters.size()) {
    Controls.filters.push_back(std::make_pair(num, den));
  } else {
    Controls.filters[index] = std::make_pair(num, den);
  }
}

void ChangeHighShelf(unsigned int index, double gaindB, double cofreq) {
  unsigned int FS = 44100;
  const double pi = 3.14159265358979323846;
  const double gain = std::pow(10, (gaindB / 20));
  const double angcofreq = (cofreq * 2 * pi) / FS;
  std::vector<double> num, den;
  num.push_back((std::sqrt(gain) * std::tan(angcofreq / 2) + gain) /
                (std::sqrt(gain) * std::tan(angcofreq / 2) + 1));
  num.push_back((std::sqrt(gain) * std::tan(angcofreq / 2) - gain) /
                (std::sqrt(gain) * std::tan(angcofreq / 2) + 1));
  den.push_back((std::sqrt(gain) * std::tan(angcofreq / 2) - 1) /
                (std::sqrt(gain) * std::tan(angcofreq / 2) + 1));
  if (index >= Controls.filters.size()) {
    Controls.filters.push_back(std::make_pair(num, den));
  } else {
    Controls.filters[index] = std::make_pair(num, den);
  }
}

void Filter(double* input, unsigned int filter, unsigned int channel,
            unsigned int inputsize) {
  std::vector<double> num = std::get<0>(Controls.filters[filter]);
  std::vector<double> den = std::get<1>(Controls.filters[filter]);
  double iprev, oprev;
  double output[inputsize];
  if (channel == 1) {
    iprev = Controls.previousSamples[filter][0].first.first;
    oprev = Controls.previousSamples[filter][0].first.second;
  } else {
    iprev = Controls.previousSamples[filter][0].second.first;
    oprev = Controls.previousSamples[filter][0].second.first;
  }
  output[0] = num[0] * input[0] + num[1] * iprev - den[0] * oprev;

  for (std::size_t i = 1; i < inputsize; ++i) {
    output[i] =
        (num[0] * input[i] + num[1] * input[i - 1] - den[0] * output[i - 1]);
    if (i == inputsize - 1) {
      if (channel == 1) {
        Controls.previousSamples[filter][0].first.first = input[i];
        Controls.previousSamples[filter][0].first.second = output[i];
      } else {
        Controls.previousSamples[filter][0].second.first = input[i];
        Controls.previousSamples[filter][0].second.second = output[i];
      }
    }
  }
  memcpy(input, output, inputsize * sizeof(double));
}

void Scale(double* input, double gaindB, unsigned int inputsize) {
  // Scale the input
  const double gain = std::pow(10, (gaindB / 20));
  double output[inputsize];
  for (unsigned int i = 0; i < inputsize; i++) {
    output[i] = gain * input[i];
  }
  memcpy(input, output, inputsize * sizeof(double));
}
}  // namespace EQ
