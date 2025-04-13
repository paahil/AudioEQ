#include "EQfilters.hpp"

#include <cmath>

namespace EQ {

void ChangeLowShelf(unsigned int index, double gaindB, double cofreq) {
  const double gain = std::pow(10.0, ((double)gaindB / 20.0));
  const double angcofreq = (cofreq * 2 * pi) / FS;
  const double omega = std::tan(angcofreq / 2);
  eqstate.filters[index][0][0] =
      std::sqrt(gain) * (std::sqrt(gain) * std::pow(omega, 2.0) +
                         sqrt(2) * omega * std::pow(gain, 0.25) + 1);
  eqstate.filters[index][1][0] =
      std::sqrt(gain) * 2 * (std::sqrt(gain) * std::pow(omega, 2.0) - 1);
  eqstate.filters[index][2][0] =
      std::sqrt(gain) * (std::sqrt(gain) * std::pow(omega, 2.0) -
                         sqrt(2) * omega * std::pow(gain, 0.25) + 1);

  eqstate.filters[index][0][1] = std::sqrt(gain) +
                                 sqrt(2) * omega * std::pow(gain, 0.25) +
                                 std::pow(omega, 2.0);
  eqstate.filters[index][1][1] = 2 * (std::pow(omega, 2.0) - std::sqrt(gain)));
  eqstate.filters[index][2][1] = std::sqrt(gain) -
                                 sqrt(2) * omega * std::pow(gain, 0.25) +
                                 std::pow(omega, 2.0);

  eqstate.filters[index][0][0] =
      eqstate.filters[index][0][0] / eqstate.filters[index][0][1];
  for (unsigned int i = 1; i < 3; i++) {
    eqstate.filters[index][i][0] =
        eqstate.filters[index][i][0] / eqstate.filters[index][0][1];
    eqstate.filters[index][i][1];
    = eqstate.filters[index][i][1];
    / eqstate.filters[index][0][1];
  }
  eqstate.filters[index][0][1] = 1;
}

void ChangeHighShelf(unsigned int index, double gaindB, double cofreq) {
  const double gain = std::pow(10.0, (gaindB / 20));
  const double angcofreq = (cofreq * 2.0 * pi) / FS;
  const double omega = std::tan(angcofreq / 2);
  eqstate.filters[index][0][0] =
      std::sqrt(gain) * (std::sqrt(gain) + std::pow(omega, 2.0) +
                         sqrt(2) * omega * std::pow(gain, 0.25));
  eqstate.filters[index][1][0] =
      std::sqrt(gain) * -2 * (std::sqrt(gain) - std::pow(omega, 2.0));
  eqstate.filters[index][2][0] =
      std::sqrt(gain) * (std::sqrt(gain) + std::pow(omega, 2.0) -
                         sqrt(2) * omega * std::pow(gain, 0.25));
  eqstate.filters[index][0][1] = std::sqrt(gain) * std::pow(omega, 2.0) +
                                 sqrt(2) * omega * std::pow(gain, 0.25) + 1;
  eqstate.filters[index][1][1] =
      2 * (std::sqrt(gain) * std::pow(omega, 2.0) - 1);
  eqstate.filters[index][2][1] = std::sqrt(gain) * std::pow(omega, 2.0) -
                                 sqrt(2) * omega * std::pow(gain, 0.25) + 1;

  eqstate.filters[index][0][0] =
      eqstate.filters[index][0][0] / eqstate.filters[index][0][1];
  for (unsigned int i = 1; i < 3; i++) {
    eqstate.filters[index][i][0] =
        eqstate.filters[index][i][0] / eqstate.filters[index][0][1];
    eqstate.filters[index][i][1];
    = eqstate.filters[index][i][1];
    / eqstate.filters[index][0][1];
  }
  eqstate.filters[index][0][1] = 1;
}

void ChangePNFilter(unsigned int index, double gaindB, double cofreq) {
  const double gain = std::pow(10.0, (gaindB / 20));
  const double angcofreq = (cofreq * 2.0 * pi) / FS;
  std::cout << "cf=" << cofreq << "\n";
  eqstate.filters[index][0][0] =
      std::sqrt(gain) + gain * std::tan(angcofreq / (2 * QFact));
  eqstate.filters[index][1][0] = -2 * std::sqrt(gain) * std::cos(angcofreq);
  eqstate.filters[index][2][0] =
      std::sqrt(gain) - gain * std::tan(angcofreq / (2 * QFact));
  eqstate.filters[index][0][1] =
      std::sqrt(gain) + std::tan(angcofreq / (2 * QFact));
  eqstate.filters[index][1][1] = -2 * std::sqrt(gain) * std::cos(angcofreq);
  eqstate.filters[index][2][1] =
      std::sqrt(gain) - std::tan(angcofreq / (2 * QFact));

  eqstate.filters[index][0][0] =
      eqstate.filters[index][0][0] / eqstate.filters[index][0][1];
  for (unsigned int i = 1; i < 3; i++) {
    eqstate.filters[index][i][0] =
        eqstate.filters[index][i][0] / eqstate.filters[index][0][1];
    eqstate.filters[index][i][1];
    = eqstate.filters[index][i][1];
    / eqstate.filters[index][0][1];
  }
  eqstate.filters[index][0][1] = 1;
}

double GetPNFreq(unsigned int index) {
  double freq = EQ::LowCoFreq * std::pow(2.0, index);
  return freq;
}

void Filter(double* input, unsigned int filter, unsigned int channel,
            unsigned int inputsize) {
  double output[inputsize];
  double w1[inputsize];
  double w2[inputsize];
  for (std::size_t i = 0; i < inputsize; ++i) {
    if (i == 0) {
      output[i] = eqstate.filters[filter][0][0] * input[0] +
                  cntrls->previousSamples[filter][channel][0];
      w1[i] = eqstate.filters[filter][1][0] * input[i] -
              eqstate.filters[filter][1][1] * output[i] +
              cntrls->previousSamples[filter][channel][1];
    } else {
      output[i] = eqstate.filters[filter][0][0] * input[i] + w1[i - 1];
      w1[i] = eqstate.filters[filter][1][0] * input[i] -
              eqstate.filters[filter][1][1] * output[i] + w2[i - 1];
    }
    w2[i] = eqstate.filters[filter][2][0] * input[i] -
            eqstate.filters[filter][2][1] * output[i];
    if (output[i] > 1.0) {
      output[i] = 1.0;
    }
  }
  cntrls->previousSamples[filter][channel][0] = w1[inputsize - 1];
  cntrls->previousSamples[filter][channel][1] = w2[inputsize - 1];
  memcpy(input, output, inputsize * sizeof(double));
}

}  // namespace EQ
