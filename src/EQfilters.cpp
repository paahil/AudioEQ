#include "EQfilters.hpp"

#include <cmath>

#include "aquila.h"
namespace EQ {
double* LowShelf(double* filterdata, double gaindB, double cofreq,
                 unsigned int inputsize) {
  const double gain = std::pow(10, (gaindB / 20));
  unsigned int winsize = inputsize / sizeof(double);
  unsigned int FS = 44100;
  const double pi = 3.14159265358979323846;
  const std::complex<double> i1(0, 1);
  std::cout << "i=" << i1 << std::endl;
  auto fft = Aquila::FftFactory::getFft(winsize);
  Aquila::SpectrumType spectrum = fft->fft(filterdata);
  // generate a low-pass filter spectrum
  Aquila::SpectrumType filterSpectrum(winsize);
  for (std::size_t i = 0; i < winsize; ++i) {
    double f = (i * FS * 0.5) / winsize;
    filterSpectrum[i] = ((gain * std::tan(pi * cofreq) + std::sqrt(gain)) +
                         (gain * std::tan(pi * cofreq) - std::sqrt(gain)) *
                             std::exp(-2 * pi * f * i1)) /
                        ((std::tan(pi * cofreq) + std::sqrt(gain)) +
                         (std::tan(pi * cofreq) - std::sqrt(gain)) *
                             std::exp(-2 * pi * f * i1));
  }

  // the following line does the multiplication of two spectra
  // (which is complementary to convolution in time domain)
  std::transform(
      std::begin(spectrum), std::end(spectrum), std::begin(filterSpectrum),
      std::begin(spectrum),
      [](Aquila::ComplexType x, Aquila::ComplexType y) { return x * y; });

  // Inverse FFT moves us back to time domain
  double output[winsize];
  fft->ifft(spectrum, output);
  memcpy(filterdata, output, inputsize);
  return filterdata;
}
}  // namespace EQ
