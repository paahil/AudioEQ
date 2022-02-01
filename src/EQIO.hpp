#ifndef EQIO_HPP
#define EQIO_HPP
#include <iostream>

#include "../libs/rtaudio/RtAudio.h"
namespace EQ {
int RWSoundCard(void *outputBuffer, void *inputBuffer,
                unsigned int nBufferFrames, double streamTime,
                RtAudioStreamStatus status, void *data);
}

#endif