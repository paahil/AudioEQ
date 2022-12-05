#ifndef EQCONTROLSHPP
#define EQCONTROLSHPP
#include <iostream>
#include <vector>

#include "../libs/rtaudio/RtAudio.h"
namespace EQ {
enum FiltTypes { LShelf, HShelf, ParamEQ };

const int LowCoFreq = 120;
const int HighCoFreq = 12000;
const double QFact = 1.0;

struct EQControls {
  int filternum;
  std::vector<std::vector<double>> previousSamples;
  std::vector<std::pair<std::vector<double>, std::vector<double>>>
      filters;  // vector of pairs containing numerator and denominator
                // coeficcients
  RtAudio adac = RtAudio();
  int outputnum;                      // Number of output devices
  int inputnum;                       // Number of input devices
  RtAudio::StreamParameters oParams;  // Output paremetres
  RtAudio::StreamParameters iParams;  // Input parametres
  unsigned int bufferFrames = 50 * 256;
  unsigned int bufferBytes = 0;
};

void ChangeInputDevice(EQControls* cntrls, int id);
void ChangeOutputDevice(EQControls* cntrls, int id);
}  // namespace EQ

#endif