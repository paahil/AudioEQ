#ifndef EQCONTROLSHPP
#define EQCONTROLSHPP
#include <iostream>
#include <vector>

#include "../libs/rtaudio/RtAudio.h"
namespace EQ {
enum FiltTypes { LShelf, HShelf, ParamEQ };

struct EQControls {
  int filternum;                 // Number of filters
  std::vector<double> gains;     // Gains of the filters
  std::vector<double> cofreqs;   // Cut-off frequencies of the filters
  std::vector<FiltTypes> types;  // Types of the filters
  RtAudio adac;
  int outputnum;                      // Number of output devices
  int inputnum;                       // Number of input devices
  RtAudio::StreamParameters oParams;  // Output paremetres
  RtAudio::StreamParameters iParams;  // Input parametres
  unsigned int bufferFrames = 512;
  unsigned int bufferBytes = bufferFrames * 8;
};

extern EQControls Controls;

void ChangeInputDevice(int id);
void ChangeOutputDevice(int id);
}  // namespace EQ

#endif