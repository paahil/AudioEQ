#include "EQIO.hpp"

#include <iostream>
#include <vector>

#include "EQcontrols.hpp"
#include "EQfilters.hpp"
namespace EQ {
int RWSoundCard(void *outputBuffer, void *inputBuffer,
                unsigned int nBufferFrames, double streamTime,
                RtAudioStreamStatus status, void *data) {
  // Since the number of input and output channels is equal, we can do
  // a simple buffer copy operation here.
  if (status) std::cout << "Stream over/underflow detected." << std::endl;
  unsigned int *bytes = (unsigned int *)data;
  unsigned int SIZE = *bytes / sizeof(double);
  double input[SIZE];
  memcpy(input, inputBuffer, *bytes);
  auto fft = Aquila::FftFactory::getFft(SIZE);
  Aquila::SpectrumType spectrum = fft->fft(input);
  int len = Controls.filternum - 1;
  for (int i = 0; i <= len; i++) {
    spectrum = Filter(spectrum, Controls.filtspects[i],*bytes);
  }
  //EQ::Normalize((double*) inputBuffer, filterdata, 0, *bytes);
  double output[SIZE];
  fft->ifft(spectrum, output);
  memcpy(outputBuffer, output, *bytes);
  return 0;
}

int ToggleEQ(ToggleEQenum a) {
  switch (a) {
    case On:
      try {
        Controls.adac.openStream(&Controls.oParams, &Controls.iParams,
                                 RTAUDIO_FLOAT64, 44100, &Controls.bufferFrames,
                                 &RWSoundCard, (void *)&Controls.bufferBytes);
      } catch (RtAudioErrorType &e) {
        // e.printMessage();
        std::cout << "Error Open" << std::endl;
        return -1;
      }
      try {
        Controls.adac.startStream();
      } catch (RtAudioErrorType &e) {
        std::cout << "Error Start" << std::endl;
        // e.printMessage();
        return -1;
      }
      break;
    case Off:
      try {
        Controls.adac.stopStream();
      } catch (RtAudioErrorType &e) {
        // e.printMessage();
        std::cout << "Error Stop" << std::endl;
        return -1;
      }
      break;
    default:
      break;
  }
  return 0;
}
}  // namespace EQ