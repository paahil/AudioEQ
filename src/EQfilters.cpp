#include "EQfilters.hpp"

#include "aquila.h"
namespace EQ {
std::vector<double> LowShelf(std::vector<double> input, double dB,
                             double cofreq) {
  const double gain = std::pow(10, (dB / 20));
  const std::size_t winsize = input.size();
  const std::size_t FS = 44100;
  auto fft = Aquila::FftFactory::getFft(winsize);
  Aquila::SpectrumType spectrum = fft->fft(input.data());
  // generate a low-pass filter spectrum
  Aquila::SpectrumType filterSpectrum(winsize);
  for (std::size_t i = 0; i < winsize; ++i) {
    if (i < (winsize * 120 / FS)) {
      // passband
      filterSpectrum[i] = gain;
    } else {
      // stopband
      filterSpectrum[i] = 1.0;
    }
  }

  // the following line does the multiplication of two spectra
  // (which is complementary to convolution in time domain)
  std::transform(
      std::begin(spectrum), std::end(spectrum), std::begin(filterSpectrum),
      std::begin(spectrum),
      [](Aquila::ComplexType x, Aquila::ComplexType y) { return x * y; });

  // Inverse FFT moves us back to time domain
  double x1[winsize];
  fft->ifft(spectrum, x1);
  std::vector<double> output;
  for (std::size_t i = 0; i < winsize; ++i) {
    output.push_back(x1[i]);
  }
  return output;
}
}  // namespace EQ
