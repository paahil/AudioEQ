#ifndef EQCONTROLSHPP
#define EQCONTROLSHPP
#include "../libs/rtaudio/RtAudio.h"
namespace EQ {
const double pi = 3.14159265358979323846;
// Number of filters in the EQ
const int nfilter = 5;
// Number of audio channels
const int nchannel = 2;
// Filter order
const int filtord = 2;
// Number of samples per window
const int nsamp = 1024;
// Total number of samples (size of the buffer in samples)
const unsigned int nsamptotal = nchannel * nsamp;
// Length of the audio buffer in bytes
const unsigned int bufferlen = bufferFrames * sizeof(double);
// Mutex for output array to avoid conflict between writing by the audio stream
// and calculating the spectrum in GUI
std::mutex outputmutex;
struct EQState {
  /*
  2-D array containing last N = filter order samples of the previous window for
  all channels to provide seamless transition between sampling windows
  */
  double[nchannel][filtord] prevsamp = {0};
  /*
  3-D array containing filter coefficients for all filters (numerator [m][n][0],
  denominator[[m][n][1]])
  */
  double[nfilter][filtord + 1][2] filters = {0};
  // Audio handler (RtAudio)
  RtAudio adac = RtAudio();
  // Number of output devices
  int noutput = 0;
  // Current output device id
  int outputid = 0;
  // Number of input devices
  int ninput = 0;
  // Current input device id
  int inputid = 0;
  RtAudio::StreamParameters oParams;  // Output parametres
  RtAudio::StreamParameters iParams;  // Input parametres
  // 2-D array containing output audio samples for each channel
  double[nchannel][nsamp] eqoutput = {0};
} eqstate;

}  // namespace EQ
#endif