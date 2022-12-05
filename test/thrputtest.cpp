#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "RtAudio.h"
#include "aquila.h"
std::vector<double> prevsamp1(2);
std::vector<double> prevsamp2(2);
const double pi = 3.14159265358979323846;
double db = 25.0;
double gain = std::pow(10.0, (db / 20));
double angcofreq = 2 * pi * (120.0 / 44100);
double b0 = ((gain * std::tan(angcofreq / 2) + std::sqrt(gain)) /
             (std::tan(angcofreq / 2) + std::sqrt(gain)));
double b1 = (gain * std::tan(angcofreq / 2) - std::sqrt(gain)) /
            (std::tan(angcofreq / 2) + std::sqrt(gain));
double a1 = (std::tan(angcofreq / 2) - std::sqrt(gain)) /
            (std::tan(angcofreq / 2) + std::sqrt(gain));
/*
double b0 = 1.0312;
double b1 = -0.9651;
double a1 = -0.9963;*/

void filter(double *input, unsigned int size, unsigned int indx) {
  double output[size];
  std::cout << b0 << ", " << b1 << ", " << a1 << "\n";
  if (indx == 1) {
    output[0] = b0 * input[0] + b1 * prevsamp1[0] - a1 * prevsamp1[1];
  } else {
    output[0] = b0 * input[0] + b1 * prevsamp2[0] - a1 * prevsamp2[1];
  }

  for (std::size_t i = 1; i < size; ++i) {
    output[i] = b0 * input[i] + b1 * input[i - 1] - a1 * output[i - 1];
    if (i == size - 1) {
      if (indx == 1) {
        prevsamp1[0] = input[i];
        prevsamp1[1] = output[i];
      } else {
        prevsamp2[0] = input[i];
        prevsamp2[1] = output[i];
      }
    }
  }
  memcpy(input, output, size * sizeof(double));
  // std::cout << "post" << prevsamp1[0] << " ";
}

// Pass-through function.
int inout(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
          double streamTime, RtAudioStreamStatus status, void *data) {
  auto start = std::chrono::steady_clock::now();
  if (status) std::cout << "Stream over/underflow detected." << std::endl;

  unsigned int *bytes = (unsigned int *)data;
  unsigned int SIZE = *bytes / sizeof(double);
  double input[SIZE];
  memcpy(input, inputBuffer, *bytes);
  double channel1[SIZE / 2];
  double channel2[SIZE / 2];
  auto istop = std::chrono::steady_clock::now();
  std::cout << "INIT: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(istop -
                                                                    start)
                   .count()
            << " ns" << std::endl;
  auto cstart = std::chrono::steady_clock::now();
  for (unsigned int i = 0; i < SIZE; i++) {
    if (i % 2 == 0) {
      channel1[i / 2] = input[i];
    } else {
      channel2[i / 2] = input[i];
    }
  }
  auto cstop = std::chrono::steady_clock::now();
  std::cout << ", Channel split: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(cstop -
                                                                    cstart)
                   .count()
            << " ns" << std::endl;
  auto fstart = std::chrono::steady_clock::now();
  filter(channel1, SIZE / 2, 1);
  filter(channel2, SIZE / 2, 2);
  auto fstop = std::chrono::steady_clock::now();
  std::cout << ", Filtering: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(cstop -
                                                                    cstart)
                   .count()
            << " ns" << std::endl;
  auto ostart = std::chrono::steady_clock::now();
  double output[SIZE];
  for (unsigned int i = 0; i < SIZE; i++) {
    if (i % 2 == 0) {
      output[i] = channel1[i / 2];
    } else {
      output[i] = channel2[i / 2];
    }
  }
  // EQ::Normalize(input, output, 0, SIZE);
  memcpy(outputBuffer, output, *bytes);
  auto stop = std::chrono::steady_clock::now();
  std::cout << ", Output Formatting: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(stop -
                                                                    ostart)
                   .count()
            << " ns" << std::endl;
  std::cout << ", TOTAL: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(stop -
                                                                    start)
                   .count()
            << " ns" << std::endl;
  return 0;
}
int main() {
  std::cout << gain << " " << angcofreq << std::endl;
  std::cout << b0 << " " << b1 << " " << a1 << std::endl;
  RtAudio adac;
  if (adac.getDeviceCount() < 1) {
    std::cout << "\nNo audio devices found!\n";
    exit(0);
  }
  // Set the same number of channels for both input and output.
  unsigned int bufferBytes, bufferFrames = 512 * 1;
  RtAudio::StreamParameters iParams, oParams;
  iParams.deviceId = 4;  // Cable out
  iParams.nChannels = 2;
  oParams.deviceId = 1;  // first available device
  oParams.nChannels = 2;
  try {
    adac.openStream(&oParams, &iParams, RTAUDIO_FLOAT64, 44100, &bufferFrames,
                    &inout, (void *)&bufferBytes);
  } catch (RtAudioErrorType &e) {
    // e.printMessage();

    exit(0);
  }
  bufferBytes = bufferFrames * 2 * 8;
  try {
    adac.startStream();
    char input;
    std::cout << "\nRunning ... press <enter> to quit.\n";
    std::cin.get(input);
    // Stop the stream.
    adac.stopStream();
  } catch (RtAudioErrorType &e) {
    // e.printMessage();
    goto cleanup;
  }
cleanup:
  if (adac.isStreamOpen()) adac.closeStream();
  return 0;
}
