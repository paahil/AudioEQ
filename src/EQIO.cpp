#include "EQIO.hpp"

#include <chrono>
#include <iostream>
#include <vector>

#include "EQcontrols.hpp"
#include "EQfilters.hpp"
namespace EQ {
int RWSoundCard(void *outputBuffer, void *inputBuffer,
                unsigned int nBufferFrames, double streamTime,
                RtAudioStreamStatus status, void *data) {
  auto start = std::chrono::steady_clock::now();
  if (status) std::cout << "Stream over/underflow detected." << std::endl;
  EQControls *cntrls = (EQControls *)data;
  unsigned int bytes = nBufferFrames * 2 * 8;
  unsigned int SIZE = bytes / sizeof(double);
  double input[SIZE];
  memcpy(input, inputBuffer, bytes);
  double channel1[SIZE / 2];
  double channel2[SIZE / 2];
  /*auto istop = std::chrono::steady_clock::now();
  std::cout << "INIT: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(istop -
                                                                    start)
                   .count()
            << " ns" << std::endl;
  auto cstart = std::chrono::steady_clock::now();*/
  for (unsigned int i = 0; i < SIZE; i++) {
    if (i % 2 == 0) {
      channel1[i / 2] = input[i];
    } else {
      channel2[i / 2] = input[i];
    }
  }

  /*auto cstop = std::chrono::steady_clock::now();
  std::cout << ", Channel split: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(cstop -
                                                                    cstart)
                   .count()
            << " ns" << std::endl;*/
  auto fstart = std::chrono::steady_clock::now();
  for (int i = 0; i < cntrls->filternum; i++) {
    Filter(cntrls, channel1, i, 1, SIZE / 2);
    Filter(cntrls, channel2, i, 2, SIZE / 2);
  }
  auto fstop = std::chrono::steady_clock::now();
  /*std::cout << ", Filtering: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(fstop -
                                                                    fstart)
                   .count()
            << " ns" << std::endl; /*
   auto ostart = std::chrono::steady_clock::now();*/
  double output[SIZE];
  for (unsigned int i = 0; i < SIZE; i++) {
    if (i % 2 == 0) {
      output[i] = channel1[i / 2];
    } else {
      output[i] = channel2[i / 2];
    }
  }

  memcpy(outputBuffer, output, bytes);
  auto stop = std::chrono::steady_clock::now();
  /* std::cout << ", Output Formatting: "
             << std::chrono::duration_cast<std::chrono::nanoseconds>(stop -
                                                                     ostart)
                    .count()
             << " ns" << std::endl;*/
  /*std::cout << ", TOTAL: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(stop -
                                                                    start)
                   .count()
            << " ns" << std::endl;*/
  return 0;
}

int ToggleEQ(EQControls *cntrls, ToggleEQenum a) {
  switch (a) {
    case On:
      try {
        cntrls->adac.openStream(&cntrls->oParams, &cntrls->iParams,
                                RTAUDIO_FLOAT64, 44100, &cntrls->bufferFrames,
                                &RWSoundCard, (void *)cntrls);
        cntrls->bufferBytes = cntrls->bufferFrames * 2 * 8;
        std::cout << cntrls->bufferBytes << std::endl;
      } catch (RtAudioErrorType &e) {
        // e.printMessage();
        std::cout << "Error Open" << std::endl;
        return -1;
      }
      try {
        cntrls->adac.startStream();
      } catch (RtAudioErrorType &e) {
        std::cout << "Error Start" << std::endl;
        // e.printMessage();
        return -1;
      }
      break;
    case Off:
      try {
        cntrls->adac.stopStream();
      } catch (RtAudioErrorType &e) {
        // e.printMessage();
        std::cout << "Error Stop" << std::endl;
        return -1;
      }
      break;
    default:
      break;
  }
  return 0;
}
}  // namespace EQ