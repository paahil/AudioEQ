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
  int filternum;                 // Number of filters
  std::vector<double> gains;     // Gains of the filters
  std::vector<double> cofreqs;   // Cut-off frequencies of the filters
  std::vector<FiltTypes> types;  // Types of the filters
  std::vector<Aquila::SpectrumType> filtspects;
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