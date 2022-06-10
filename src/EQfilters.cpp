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
  std::vector<double> num,den;
  num.push_back((gain * std::tan(angcofreq / 2) + std::sqrt(gain))/(std::tan(angcofreq / 2) + std::sqrt(gain)));
  num.push_back((gain * std::tan(angcofreq / 2) - std::sqrt(gain))/(std::tan(angcofreq / 2) + std::sqrt(gain)));
  den.push_back((std::tan(angcofreq / 2) - std::sqrt(gain))/(std::tan(angcofreq / 2) + std::sqrt(gain)));
  if (index >= Controls.filters.size()) {
    Controls.filters.push_back(std::make_pair(num,den));
  } else {
    Controls.filters[index] = std::make_pair(num,den);
  }
}

void ChangeHighShelf(unsigned int index, double gaindB, double cofreq) {
  unsigned int FS = 44100;
  const double pi = 3.14159265358979323846;
  const double gain = std::pow(10, (gaindB / 20));
  const double angcofreq = (cofreq * 2 * pi) / FS;
  std::vector<double> num,den;
  num.push_back((std::sqrt(gain) * std::tan(angcofreq / 2) + gain)/(std::sqrt(gain) * std::tan(angcofreq / 2) + 1));
  num.push_back((std::sqrt(gain) * std::tan(angcofreq / 2) - gain)/(std::sqrt(gain) * std::tan(angcofreq / 2) + 1));
  den.push_back((std::sqrt(gain) * std::tan(angcofreq / 2) - 1)/(std::sqrt(gain) * std::tan(angcofreq / 2) + 1));
  if (index > Controls.filters.size()) {
    Controls.filters.push_back(std::make_pair(num,den));
  } else {
    Controls.filters[index] = std::make_pair(num,den);
  }
}

void Filter(double* input, unsigned int filter, unsigned int channel, unsigned int inputsize) {
  std::vector<double> num = std::get<0>(Controls.filters[filter]);
  std::vector<double> den = std::get<1>(Controls.filters[filter]);
  double output[inputsize];
  if (channel == 1) {
    output[0] = num[0] * input[0] + num[1] * Controls.previousSamples[0] - den[0] * Controls.previousSamples[1];
  } else {
    output[0] = num[0] * input[0] + num[1] * Controls.previousSamples[3] - den[0] * Controls.previousSamples[4];
  }
  // output[0] = 0;
  //  std::cout << "pre" << prevsamp1[0] << " ";
  float inputmax = input[0];
  float outputmax = output[0];
  for (std::size_t i = 1; i < inputsize; ++i) {
    output[i] = num[0] * input[i] + num[1] * input[i - 1] + den[0] * output[i - 1];
    if (i == inputsize - 1) {
      if (channel == 1) {
        Controls.previousSamples[0] = input[i];
        Controls.previousSamples[1] = output[i];
      } else {
        Controls.previousSamples[3] = input[i];
        Controls.previousSamples[4] = output[i];
      }
    }
  }
  memcpy(input, output, inputsize*sizeof(double));
}

double* Normalize(double* input, double* filterdata, double gaindB,
                  unsigned int inputsize) {
  // Normalize output
  const double gain = std::pow(10, (gaindB / 20));
  double maxorig = input[0];
  double maxfilt = filterdata[0];

  for (unsigned int i = 0; i < inputsize; i++) {
    if (input[i] > maxorig) {
      maxorig = input[i];
    }
    if (filterdata[i] > maxfilt) {
      maxfilt = filterdata[i];
    }
  }

  for (unsigned int i = 0; i < inputsize; i++) {
    filterdata[i] = gain * (maxorig * filterdata[i] / maxfilt);
  }

  return filterdata;
}
}  // namespace EQ
