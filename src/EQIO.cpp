#include "EQIO.hpp"

#include <chrono>
#include <cmath>
#include <complex>
#include <csignal>
#include <iostream>
#include <vector>

#include "EQcontrols.hpp"
#include "EQfilters.hpp"
namespace EQ {
unsigned int BitReverse(unsigned int x, int log2n) {
  int n = 0;
  int mask = 0x1;
  for (int i = 0; i < log2n; i++) {
    n <<= 1;
    n |= (x & 1);
    x >>= 1;
  }
  return n;
}

void CalculateSpectrum(EQControls *cntrls, double *sig, unsigned int len) {
  typedef std::complex<double> cmplx;
  const cmplx J(0, 1);
  const double PI = 3.1415926536;
  unsigned int flen = len / 2;
  unsigned int log2n = std::log2(len);
  cmplx b[len];

  unsigned int n = 1 << log2n;
  for (unsigned int i = 0; i < n; ++i) {
    b[BitReverse(i, log2n)] = sig[i];
  }
  for (int s = 1; s <= log2n; ++s) {
    int m = 1 << s;
    int m2 = m >> 1;
    cmplx w(1, 0);
    cmplx wm = exp(-J * (PI / m2));
    for (unsigned int j = 0; j < m2; ++j) {
      for (unsigned int k = j; k < n; k += m) {
        cmplx t = w * b[k + m2];
        cmplx u = b[k];
        b[k] = u + t;
        b[k + m2] = u - t;
      }
      w = w * wm;
    }
  }
  for (unsigned int k = 0; k < flen; k++) {
    cntrls->magspec[k] = 20 * std::log10(std::abs(b[k]) / len);
  }
}

int RWSoundCard(void *outputBuffer, void *inputBuffer,
                unsigned int nBufferFrames, double streamTime,
                RtAudioStreamStatus status, void *data) {
  if (status) std::cout << "Stream over/underflow detected." << std::endl;
  EQControls *cntrls = (EQControls *)data;
  unsigned int bytes = nBufferFrames * 2 * 8;
  unsigned int SIZE = bytes / sizeof(double);
  double input[SIZE];
  memcpy(input, inputBuffer, bytes);
  double channel1[SIZE / 2];
  double channel2[SIZE / 2];

  for (unsigned int i = 0; i < SIZE; i++) {
    if (i % 2 == 0) {
      channel1[i / 2] = input[i];
    } else {
      channel2[i / 2] = input[i];
    }
  }

  for (int i = 0; i < cntrls->filternum; i++) {
    Filter(cntrls, channel1, i, 0, SIZE / 2);
    Filter(cntrls, channel2, i, 1, SIZE / 2);
  }
  if (streamTime > cntrls->lastupdt + (double)(1 / (cntrls->FPS))) {
    CalculateSpectrum(cntrls, channel1, SIZE / 2);
    // std::cout << "joo\n";
  }
  double output[SIZE];
  for (unsigned int i = 0; i < SIZE; i++) {
    if (i % 2 == 0) {
      output[i] = channel1[i / 2];
    } else {
      output[i] = channel2[i / 2];
    }
  }
  memcpy(outputBuffer, output, bytes);
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