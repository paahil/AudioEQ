#ifndef EQCONTROLSHPP
#define EQCONTROLSHPP
#include <iostream>
#include <vector>

#include "../libs/aquila/aquila/aquila.h"
#include "../libs/rtaudio/RtAudio.h"
namespace EQ {
enum FiltTypes { LShelf, HShelf, ParamEQ };

const int LowCoFreq = 120;
const int HighCoFreq = 18000;
const double QFact = 1.0;

struct EQControls {
  int filternum;
  std::vector<double> previousSamples;
  std::vector<std::pair<std::vector<double>,std::vector<double>>> filters; // vector of pairs containing numerator and denominator coeficcients
  RtAudio adac;
  int outputnum;                      // Number of output devices
  int inputnum;                       // Number of input devices
  RtAudio::StreamParameters oParams;  // Output paremetres
  RtAudio::StreamParameters iParams;  // Input parametres
  unsigned int bufferFrames = 2048;
  unsigned int bufferBytes = bufferFrames * 2 * 8;
};

extern EQControls Controls;

void ChangeInputDevice(int id);
void ChangeOutputDevice(int id);
}  // namespace EQ

#endif