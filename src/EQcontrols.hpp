#ifndef EQCONTROLSHPP
#define EQCONTROLSHPP
#include <iostream>
#include <vector>

#include "../libs/rtaudio/RtAudio.h"
namespace EQ {
enum FiltTypes { LShelf, HShelf, ParamEQ };

const int LowCoFreq = 80;
const int HighCoFreq = 10240;
const int MidBand = HighCoFreq - LowCoFreq;
const double QFact = 2.0;
const unsigned int FS = 44100;
const double pi = 3.14159265358979323846;

struct EQControls {
  int filternum;  // Number of filters in the EQ
  std::vector<std::vector<std::vector<double>>>
      previousSamples;  // vector of pairs (input and output) of pairs
                        // (channels 1 and 2) containing N=filter order of
                        // previous samples
  std::vector<std::pair<std::vector<double>, std::vector<double>>>
      filters;  // vector of pairs containing numerator and denominator
                // coeficcients
  RtAudio adac = RtAudio();
  int outputnum;                         // Number of output devices
  int inputnum;                          // Number of input devices
  RtAudio::StreamParameters oParams;     // Output paremetres
  RtAudio::StreamParameters iParams;     // Input parametres
  unsigned int bufferFrames = 2 * 1024;  // Number of samples (1024 per channel)
  unsigned int bufferBytes = 0;
  // Vector for the magnitude spectrum of the output (dB)
  std::vector<double> magspec;
  double lastupdt = 0;    // Last previous timestamp for screen refresh
  unsigned int FPS = 20;  // Refresh rate
};

void ChangeInputDevice(EQControls* cntrls, int id);
void ChangeOutputDevice(EQControls* cntrls, int id);
}  // namespace EQ

#endif