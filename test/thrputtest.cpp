#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "RtAudio.h"
#include "aquila.h"
std::vector<float> prevsamp1(2);
std::vector<float> prevsamp2(2);

void filter(double *input, unsigned int size, unsigned int indx) {
  float a1 = -0.9881;
  float b0 = 1.0276;
  float b1 = -0.9604;
  double output[size];
  if (indx == 1) {
    output[0] = b0 * input[0] + b1 * prevsamp1[0] - a1 * prevsamp1[1];
  } else {
    output[0] = b0 * input[0] + b1 * prevsamp2[0] - a1 * prevsamp2[1];
  }
  // output[0] = 0;
  //  std::cout << "pre" << prevsamp1[0] << " ";
  float inputmax = input[0];
  float outputmax = output[0];
  for (std::size_t i = 1; i < size; ++i) {
    output[i] = b0 * input[i] + b1 * input[i - 1] + a1 * output[i - 1];
    if (i == size - 1) {
      if (indx == 1) {
        prevsamp1[0] = input[size - 2];
        prevsamp1[1] = output[size - 2];
      } else {
        prevsamp2[0] = input[size - 2];
        prevsamp2[1] = output[size - 2];
      }
    }
  }
  memcpy(input, output, size);

  // std::cout << "post" << prevsamp1[0] << " ";
}

// Pass-through function.
int inout(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
          double streamTime, RtAudioStreamStatus status, void *data) {
  // Since the number of input and output channels is equal, we can do
  // a simple buffer copy operation here.
  if (status) std::cout << "Stream over/underflow detected." << std::endl;
  unsigned int *bytes = (unsigned int *)data;
  unsigned int SIZE = *bytes / sizeof(double);
  double input[SIZE];
  memcpy(input, inputBuffer, *bytes);
  double channel1[SIZE / 2];
  double channel2[SIZE / 2];
  for (unsigned int i = 0; i < SIZE; i++) {
    if (i % 2 == 0) {
      channel1[i / 2] = input[i];
    } else {
      channel2[i / 2] = input[i];
    }
  }
  // filter(channel1, SIZE / 2, 1);
  // filter(channel2, SIZE / 2, 2);
  double output[SIZE];
  for (unsigned int i = 0; i < SIZE; i++) {
    if (i % 2 == 0) {
      output[i] = channel1[i / 2];
    } else {
      output[i] = channel2[i / 2];
    }
  }
  memcpy(outputBuffer, output, *bytes);
  // memcpy(outputBuffer, inputBuffer, *bytes);
  return 0;
}
int main() {
  RtAudio adac;
  if (adac.getDeviceCount() < 1) {
    std::cout << "\nNo audio devices found!\n";
    exit(0);
  }
  // Set the same number of channels for both input and output.
  unsigned int bufferBytes, bufferFrames = 512;
  RtAudio::StreamParameters iParams, oParams;
  iParams.deviceId = 6;  // Cable out
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
