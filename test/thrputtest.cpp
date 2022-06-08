#include <cstdlib>
#include <cstring>
#include <iostream>

#include "RtAudio.h"
#include "aquila.h"
double *filter(double *filterdata, unsigned int size) {
  unsigned int winsize = size / sizeof(double);
  unsigned int FS = 44100;
  auto fft = Aquila::FftFactory::getFft(winsize);
  std::cout << "In Low shelf" << std::endl;
  Aquila::SpectrumType spectrum = fft->fft(filterdata);
  std::cout << "After FFT" << std::endl;
  // generate a low-pass filter spectrum
  Aquila::SpectrumType filterSpectrum(winsize);
  for (std::size_t i = 0; i < winsize; ++i) {
    if (i < (winsize * 120 / FS)) {
      // passband
      filterSpectrum[i] = 1.0;
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
  double output[winsize];
  fft->ifft(spectrum, output);
  memcpy(filterdata, output, size);
  return filterdata;
}

// Pass-through function.
int inout(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
          double streamTime, RtAudioStreamStatus status, void *data) {
  // Since the number of input and output channels is equal, we can do
  // a simple buffer copy operation here.
  if (status) std::cout << "Stream over/underflow detected." << std::endl;
  unsigned int *bytes = (unsigned int *)data;
  double *filterdata;
  filterdata = (double *)malloc(*bytes);
  memcpy(filterdata, inputBuffer, *bytes);
  filterdata = filter(filterdata, *bytes);
  memcpy(outputBuffer, filterdata, *bytes);
  free(filterdata);
  return 0;
}
int main() {
  RtAudio adac;
  if (adac.getDeviceCount() < 1) {
    std::cout << "\nNo audio devices found!\n";
    exit(0);
  }
  // Set the same number of channels for both input and output.
  unsigned int bufferBytes, bufferFrames = 512;
  RtAudio::StreamParameters iParams, oParams;
  iParams.deviceId = 6;  // Cable out
  iParams.nChannels = 2;
  oParams.deviceId = 1;  // first available device
  oParams.nChannels = 2;
  try {
    adac.openStream(&oParams, &iParams, RTAUDIO_FLOAT64, 44100, &bufferFrames,
                    &inout, (void *)&bufferBytes);
  } catch (RtAudioErrorType &e) {
    // e.printMessage();

    exit(0);
  }
  bufferBytes = bufferFrames * 2 * 8;
  try {
    adac.startStream();
    char input;
    std::cout << "\nRunning ... press <enter> to quit.\n";
    std::cin.get(input);
    // Stop the stream.
    adac.stopStream();
  } catch (RtAudioErrorType &e) {
    // e.printMessage();
    goto cleanup;
  }
cleanup:
  if (adac.isStreamOpen()) adac.closeStream();
  return 0;
}
