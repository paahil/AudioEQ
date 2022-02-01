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
  std::vector<double> input;
  std::vector<double> output;
  memcpy(&input[0], inputBuffer, *bytes);
  for (int i = 0; Controls.filternum; i++) {
    switch (Controls.types[i]) {
      case FiltTypes::LShelf:
        if (i == Controls.filternum) {
          output = EQ::LowShelf(input, Controls.gains[i], Controls.cofreqs[i]);
        }

        else {
          input = EQ::LowShelf(input, Controls.gains[i], Controls.cofreqs[i]);
        }
        break;
      case FiltTypes::HShelf:
        if (i == Controls.filternum) {
          // output = EQ::HighShelf(input, Controls.gains[i],
          // Controls.cofreqs[i]);
        }

        else {
          // input = EQ::HighShelf(input, Controls.gains[i],
          // Controls.cofreqs[i]);
        }
        break;
      default:
        break;
    }
  }
  memcpy(outputBuffer, output.data(), *bytes);
  return 0;
}
}  // namespace EQ