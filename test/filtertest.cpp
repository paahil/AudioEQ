#include "aquila.h"
int main() {
  unsigned int FS = 44100;
  std::size_t SIZE = 512;
  double gain = 0.01;
  const double pi = 3.14159265358979323846;
  double cofreq = (2500.0 / FS) * 2 * pi;
  const std::complex<double> i1(0, 1);
  std::cout << "i=" << i1 << std::endl;

  // generate a low-pass filter spectrum
  Aquila::SpectrumType filterSpectrum(SIZE);
  for (std::size_t i = 0; i < SIZE; ++i) {
    double f = (i * (double)FS) / SIZE;
    std::cout << "f=" << f << ", ";
    /*std::cout << "wc=" << cofreq << ", ";
    std::cout << "b="
              << ((gain * std::tan(cofreq / 2) + std::sqrt(gain)) +
                  (gain * std::tan(cofreq / 2) - std::sqrt(gain)) *
                      std::exp(-2 * pi * i1 * (double)i))
              << ", ";
    std::cout << "a="
              << ((std::tan(pi * cofreq) + std::sqrt(gain)) +
                  (std::tan(pi * cofreq) - std::sqrt(gain)) *
                      std::exp(-2 * pi * f * i1))
              << ", ";*/
    filterSpectrum[i] = abs(((gain * std::tan(cofreq / 2) + std::sqrt(gain)) +
                             (gain * std::tan(cofreq / 2) - std::sqrt(gain)) *
                                 std::exp(-2 * pi * f * i1)) /
                            ((std::tan(cofreq / 2) + std::sqrt(gain)) +
                             (std::tan(cofreq / 2) - std::sqrt(gain)) *
                                 std::exp(-2 * pi * f * i1)));
    std::cout << filterSpectrum[i];
  }
  std::cout << std::endl;

  // the following line does the multiplication of two spectra
  // (which is complementary to convolution in time domain)

  return 0;
}