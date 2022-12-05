#ifndef EQIO_HPP
#define EQIO_HPP
#include <iostream>

#include "../libs/rtaudio/RtAudio.h"
#include "EQcontrols.hpp"

namespace EQ {
enum ToggleEQenum { On, Off };
int RWSoundCard(void *outputBuffer, void *inputBuffer,
                unsigned int nBufferFrames, double streamTime,
                RtAudioStreamStatus status, void *data);
int ToggleEQ(EQControls *cntrls, ToggleEQenum a);
}  // namespace EQ

#endif