#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "RtAudio.h"
#include "aquila.h"
std::vector<double> prevsamp1(2);
std::vector<double> prevsamp2(2);

void filter(double *input, unsigned int size, unsigned int indx) {
  double a1 = -0.9881;
  double b0 = 1.0276;
  double b1 = -0.9604;
  double output[size];
  if (indx == 1) {
    output[0] = b0 * input[0] + b1 * prevsamp1[0] - a1 * prevsamp1[1];
  } else {
    output[0] = b0 * input[0] + b1 * prevsamp2[0] - a1 * prevsamp2[1];
  }
  
  double inputmax = input[0];
  double outputmax = output[0];
  for (std::size_t i = 1; i < size; ++i) {
    output[i] = b0 * input[i] + b1 * input[i - 1] + a1 * output[i - 1];
    if (input[i] > inputmax){
      inputmax = input[i];
    }
    if (output[i]> outputmax){
      outputmax = output[i];
    }
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
  for(std::size_t i = 1; i < size; ++i) {
    output[i] = output[i]/outputmax;
  }
  memcpy(input, output, size*sizeof(double));
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
  double* channel1 = (double*) malloc(*bytes/2);
  double* channel2 = (double*) malloc(*bytes/2);
  for (unsigned int i = 0; i < SIZE; i++) {
    if (i % 2 == 0) {
      channel1[i / 2] = input[i];
    } else {
      channel2[i / 2] = input[i];
    }
  }
  filter(channel1, SIZE / 2, 1);
  filter(channel2, SIZE / 2, 2);
  double output[SIZE];
  for (unsigned int i = 0; i < SIZE; i++) {
    if (i % 2 == 0) {
      output[i] = 0.1*channel1[i / 2];
    } else {
      output[i] = 0.1*channel2[i / 2];
    }
  }
  free(channel1);
  free(channel2);
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
  unsigned int bufferBytes, bufferFrames = 512*10;
  RtAudio::StreamParameters iParams, oParams;
  iParams.deviceId = 3;  // Cable out
  iParams.nChannels = 2;
  oParams.deviceId = 0;  // first available device
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
