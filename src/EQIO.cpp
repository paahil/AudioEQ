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
  double *filterdata;
  filterdata = (double *)malloc(*bytes);
  std::cout << "IN IO" << std::endl;
  memcpy(filterdata, inputBuffer, *bytes);
  std::cout << "After memcpy" << std::endl;
  int len = Controls.filternum - 1;
  for (int i = 0; i <= len; i++) {
    switch (Controls.types[i]) {
      case FiltTypes::LShelf:
        std::cout << "Low shelf" << std::endl;
        filterdata = EQ::LowShelf(filterdata, Controls.gains[i],
                                  Controls.cofreqs[i], *bytes);
        std::cout << "After filter" << std::endl;
        break;

      case FiltTypes::HShelf:
        // input = EQ::HighShelf(input, Controls.gains[i],
        // Controls.cofreqs[i]);
        break;

      default:
        break;
    }
  }
  memcpy(outputBuffer, filterdata, *bytes);
  free(filterdata);
  std::cout << "After memcpy2" << std::endl;
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