#include "EQfilters.hpp"

#include <cmath>

namespace EQ {

void ChangeLowShelf(EQControls* cntrls, unsigned int index, double gaindB,
                    double cofreq) {
  const double gain = std::pow(10.0, ((double)gaindB / 20.0));
  const double angcofreq = (cofreq * 2 * pi) / FS;
  const double omega = std::tan(angcofreq / 2);
  std::vector<double> num, den;
  num.push_back(std::sqrt(gain) * (std::sqrt(gain) * std::pow(omega, 2.0) +
                                   sqrt(2) * omega * std::pow(gain, 0.25) + 1));
  num.push_back(std::sqrt(gain) * 2 *
                (std::sqrt(gain) * std::pow(omega, 2.0) - 1));
  num.push_back(std::sqrt(gain) * (std::sqrt(gain) * std::pow(omega, 2.0) -
                                   sqrt(2) * omega * std::pow(gain, 0.25) + 1));
  den.push_back(std::sqrt(gain) + sqrt(2) * omega * std::pow(gain, 0.25) +
                std::pow(omega, 2.0));
  den.push_back(2 * (std::pow(omega, 2.0) - std::sqrt(gain)));
  den.push_back(std::sqrt(gain) - sqrt(2) * omega * std::pow(gain, 0.25) +
                std::pow(omega, 2.0));

  num[0] = num[0] / den[0];
  for (unsigned int i = 1; i < 3; i++) {
    num[i] = num[i] / den[0];
    den[i] = den[i] / den[0];
  }
  den[0] = 1;
  if (index >= cntrls->filters.size()) {
    cntrls->filters.push_back(std::make_pair(num, den));
  } else {
    cntrls->filters[index] = std::make_pair(num, den);
  }
}

void ChangeHighShelf(EQControls* cntrls, unsigned int index, double gaindB,
                     double cofreq) {
  const double gain = std::pow(10.0, (gaindB / 20));
  const double angcofreq = (cofreq * 2.0 * pi) / FS;
  const double omega = std::tan(angcofreq / 2);
  std::vector<double> num, den;
  num.push_back(std::sqrt(gain) * (std::sqrt(gain) + std::pow(omega, 2.0) +
                                   sqrt(2) * omega * std::pow(gain, 0.25)));
  num.push_back(std::sqrt(gain) * -2 *
                (std::sqrt(gain) - std::pow(omega, 2.0)));
  num.push_back(std::sqrt(gain) * (std::sqrt(gain) + std::pow(omega, 2.0) -
                                   sqrt(2) * omega * std::pow(gain, 0.25)));
  den.push_back(std::sqrt(gain) * std::pow(omega, 2.0) +
                sqrt(2) * omega * std::pow(gain, 0.25) + 1);
  den.push_back(2 * (std::sqrt(gain) * std::pow(omega, 2.0) - 1));
  den.push_back(std::sqrt(gain) * std::pow(omega, 2.0) -
                sqrt(2) * omega * std::pow(gain, 0.25) + 1);

  num[0] = num[0] / den[0];
  for (unsigned int i = 1; i < 3; i++) {
    num[i] = num[i] / den[0];
    den[i] = den[i] / den[0];
  }
  den[0] = 1;
  if (index >= cntrls->filters.size()) {
    cntrls->filters.push_back(std::make_pair(num, den));
  } else {
    cntrls->filters[index] = std::make_pair(num, den);
  }
}

void ChangePNFilter(EQControls* cntrls, unsigned int index, double gaindB,
                    double cofreq) {
  const double gain = std::pow(10.0, (gaindB / 20));
  const double angcofreq = (cofreq * 2.0 * pi) / FS;
  std::cout << "cf=" << cofreq << "\n";
  std::vector<double> num, den;
  num.push_back(std::sqrt(gain) + gain * std::tan(angcofreq / (2 * QFact)));
  num.push_back(-2 * std::sqrt(gain) * std::cos(angcofreq));
  num.push_back(std::sqrt(gain) - gain * std::tan(angcofreq / (2 * QFact)));
  den.push_back(std::sqrt(gain) + gain * std::tan(angcofreq / (2 * QFact)));
  den.push_back(-2 * std::sqrt(gain) * std::cos(angcofreq));
  den.push_back(std::sqrt(gain) - std::tan(angcofreq / (2 * QFact)));
  num[0] = num[0] / den[0];
  for (unsigned int i = 1; i < 3; i++) {
    num[i] = num[i] / den[0];
    den[i] = den[i] / den[0];
  }
  den[0] = 1;
  if (index >= cntrls->filters.size()) {
    cntrls->filters.push_back(std::make_pair(num, den));
  } else {
    cntrls->filters[index] = std::make_pair(num, den);
  }
}

double GetPNFreq(EQControls* cntrls, unsigned int index) {
  double freq =
      EQ::LowCoFreq + (index) * (EQ::MidBand / (cntrls->filternum - 1.0));
  return freq;
}

void Filter(EQControls* cntrls, double* input, unsigned int filter,
            unsigned int channel, unsigned int inputsize) {
  std::vector<double> num = std::get<0>(cntrls->filters[filter]);
  std::vector<double> den = std::get<1>(cntrls->filters[filter]);
  double output[inputsize];
  double w1[inputsize];
  double w2[inputsize];
  for (std::size_t i = 0; i < inputsize; ++i) {
    if (i == 0) {
      output[i] =
          num[0] * input[0] + cntrls->previousSamples[filter][channel][0];
      w1[i] = num[1] * input[i] - den[1] * output[i] +
              cntrls->previousSamples[filter][channel][1];
    } else {
      output[i] = num[0] * input[i] + w1[i - 1];
      w1[i] = num[1] * input[i] - den[1] * output[i] + w2[i - 1];
    }
    w2[i] = num[2] * input[i] - den[2] * output[i];
    if (output[i] > 1.0) {
      output[i] = 1.0;
    }
  }
  cntrls->previousSamples[filter][channel][0] = w1[inputsize - 1];
  cntrls->previousSamples[filter][channel][1] = w2[inputsize - 1];
  memcpy(input, output, inputsize * sizeof(double));
}

}  // namespace EQ
