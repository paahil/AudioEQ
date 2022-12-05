#include "EQfilters.hpp"

#include <cmath>

namespace EQ {
double num[2] = {0, 0};
double den[2] = {0, 0};
double prevsamp[4] = {0, 0, 0, 0};
void ChangeLowShelf(EQControls* cntrls, unsigned int index, double gaindB,
                    double cofreq) {
  unsigned int FS = 44100;
  const double pi = 3.14159265358979323846;
  const double gain = std::pow(10.0, ((double)gaindB / 20.0));
  const double angcofreq = (cofreq * 2 * pi) / FS;
  /*num[0] = ((gain * std::tan(angcofreq / 2) + std::sqrt(gain)) /
            (std::tan(angcofreq / 2) + std::sqrt(gain)));
  num[1] = ((gain * std::tan(angcofreq / 2) - std::sqrt(gain)) /
            (std::tan(angcofreq / 2) + std::sqrt(gain)));
  den[0] = ((std::tan(angcofreq / 2) - std::sqrt(gain)) /
            (std::tan(angcofreq / 2) + std::sqrt(gain)));*/
  std::vector<double> num, den;
  num.push_back((gain * std::tan(angcofreq / 2) + std::sqrt(gain)) /
                (std::tan(angcofreq / 2) + std::sqrt(gain)));
  num.push_back((gain * std::tan(angcofreq / 2) - std::sqrt(gain)) /
                (std::tan(angcofreq / 2) + std::sqrt(gain)));
  den.push_back((std::tan(angcofreq / 2) - std::sqrt(gain)) /
                (std::tan(angcofreq / 2) + std::sqrt(gain)));
  std::cout << num[0] << ", " << num[1] << ", " << den[0] << "\n";
  if (index >= cntrls->filters.size()) {
    cntrls->filters.push_back(std::make_pair(num, den));
  } else {
    cntrls->filters[index] = std::make_pair(num, den);
  }
}

void ChangeHighShelf(EQControls* cntrls, unsigned int index, double gaindB,
                     double cofreq) {
  unsigned int FS = 44100;
  const double pi = 3.14159265358979323846;
  const double gain = std::pow(10.0, (gaindB / 20));
  const double angcofreq = (cofreq * 2.0 * pi) / FS;
  std::vector<double> num, den;
  num.push_back((std::sqrt(gain) * std::tan(angcofreq / 2) + gain) /
                (std::sqrt(gain) * std::tan(angcofreq / 2) + 1));
  num.push_back((std::sqrt(gain) * std::tan(angcofreq / 2) - gain) /
                (std::sqrt(gain) * std::tan(angcofreq / 2) + 1));
  den.push_back((std::sqrt(gain) * std::tan(angcofreq / 2) - 1) /
                (std::sqrt(gain) * std::tan(angcofreq / 2) + 1));
  std::cout << num[0] << ", " << num[1] << ", " << den[0] << "\n";
  if (index >= cntrls->filters.size()) {
    cntrls->filters.push_back(std::make_pair(num, den));
  } else {
    cntrls->filters[index] = std::make_pair(num, den);
  }
}

void Filter(EQControls* cntrls, double* input, unsigned int filter,
            unsigned int channel, unsigned int inputsize) {
  std::vector<double> num = std::get<0>(cntrls->filters[filter]);
  std::vector<double> den = std::get<1>(cntrls->filters[filter]);
  // std::cout << num[0] << ", " << num[1] << ", " << den[0] << "\n";
  double output[inputsize];
  if (channel == 1) {
    output[0] =
        (num[0] * input[0] + num[1] * cntrls->previousSamples[filter][0] -
         den[0] * cntrls->previousSamples[filter][1]);
  } else {
    output[0] =
        (num[1] * input[0] + num[0] * cntrls->previousSamples[filter][2] -
         den[0] * cntrls->previousSamples[filter][3]);
  }
  // output[0] = 0;
  //  std::cout << "pre" << prevsamp1[0] << " ";

  for (std::size_t i = 1; i < inputsize; ++i) {
    output[i] =
        (num[1] * input[i] + num[0] * input[i - 1] - den[0] * output[i - 1]);
    if (i == inputsize - 1) {
      if (channel == 1) {
        cntrls->previousSamples[filter][filter][0].first.first = input[i];
        cntrls->previousSamples[filter][filter][0].first.second = output[i];
      } else {
        cntrls->previousSamples[filter][2] = input[i];
        cntrls->previousSamples[filter][3] = output[i];
      }
    }
  }
  memcpy(input, output, inputsize * sizeof(double));
}

double* Normalize(double* input, double* filterdata, double gaindB,
                  unsigned int inputsize) {
  // Normalize output
  const double gain = std::pow(10, (gaindB / 10));
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
