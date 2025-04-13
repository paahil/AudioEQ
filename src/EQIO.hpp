#ifndef EQIO_HPP
#define EQIO_HPP
#include <iostream>

#include "../libs/rtaudio/RtAudio.h"
#include "EQcontrols.hpp"

namespace EQ {

int RWSoundCard(void *outputBuffer, void *inputBuffer,
                unsigned int nBufferFrames, double streamTime,
                RtAudioStreamStatus status, void *data);

void CalculateSpectrum(double *sig, unsigned int len);
unsigned int BitReverse(unsigned int x, int log2n);
}  // namespace EQ

#endif