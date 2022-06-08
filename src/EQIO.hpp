#ifndef EQIO_HPP
#define EQIO_HPP
#include <iostream>

#include "../libs/rtaudio/RtAudio.h"
namespace EQ {
enum ToggleEQenum { On, Off };
int RWSoundCard(void *outputBuffer, void *inputBuffer,
                unsigned int nBufferFrames, double streamTime,
                RtAudioStreamStatus status, void *data);
int ToggleEQ(ToggleEQenum a);
}  // namespace EQ

#endif