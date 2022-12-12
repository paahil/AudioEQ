#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "RtAudio.h"
#include "aquila.h"
std::vector<double> prevsamp1(3, 0.0);
std::vector<double> prevsamp2(3, 0.0);
const double pi = 3.14159265358979323846;
double db = 25.0;
double gain = std::pow(10.0, (db / 20));
double angcofreq = 2 * pi * (120.0 / 44100);
double b[] = {1.4803, -1.7759, 0.6493};
double a[] = {1, -1.9522, 0.9533};
// double b[] = {1.0312, -0.9651};
// double a[] = {1, -0.9963};

void filter(double *input, unsigned int size, unsigned int indx) {
  double output[size];
  double w1[size];
  double w2[size];
  for (std::size_t i = 0; i < size; ++i) {
    if (i == 0) {
      if (indx == 1) {
        output[i] = b[0] * input[0] + prevsamp1[0];
        w1[i] = b[1] * input[i] - a[1] * output[i] + prevsamp1[2];
      } else {
        output[i] = b[0] * input[0] + prevsamp2[0];
        w1[i] = b[1] * input[i] - a[1] * output[i] + prevsamp2[2];
      }
    } else if (i == 1) {
      if (indx == 1) {
        output[i] = b[0] * input[0] + prevsamp1[0];
        w1[i] = b[1] * input[i] - a[1] * output[i] + prevsamp1[1];
      } else {
        output[i] = b[0] * input[0] + prevsamp2[0];
        w1[i] = b[1] * input[i] - a[1] * output[i] + prevsamp2[1];
      }
    } else {
      output[i] = b[0] * input[i] + w1[i - 1];
      w1[i] = b[1] * input[i] - a[1] * output[i] + w2[i - 1];
    }

    /*if (i < 10) {
      std::cout << "in=" << input[i] << ", out=" << output[i] << "\n";
    }*/
    w2[i] = b[2] * input[i] - a[2] * output[i];
  }
  if (indx == 1) {
    prevsamp1[0] = w1[size - 1];
    prevsamp1[1] = w2[size - 1];
    prevsamp1[2] = w2[size - 2];
  } else {
    prevsamp2[0] = w1[size - 1];
    prevsamp2[1] = w2[size - 1];
    prevsamp2[2] = w2[size - 2];
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
  // std::cout << "INIT: "
  //           << std::chrono::duration_cast<std::chrono::nanoseconds>(istop -
  //                                                                   start)
  //                 .count()
  //          << " ns" << std::endl;
  auto cstart = std::chrono::steady_clock::now();
  for (unsigned int i = 0; i < SIZE; i++) {
    if (i % 2 == 0) {
      channel1[i / 2] = input[i];
    } else {
      channel2[i / 2] = input[i];
    }
  }
  auto cstop = std::chrono::steady_clock::now();
  /* std::cout << ", Channel split: "
             << std::chrono::duration_cast<std::chrono::nanoseconds>(cstop -
                                                                     cstart)
                    .count()
             << " ns" << std::endl;*/
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
