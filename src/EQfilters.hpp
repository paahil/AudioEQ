#ifndef EQ_FILTERSHPP
#define EQ_FILTERSHPP
#include <iostream>
#include <vector>

#include "EQcontrols.hpp"

namespace EQ {
enum FiltTypes { LShelf, HShelf, ParamEQ };
const int LowCoFreq = 80;
const int HighCoFreq = 10240;
const int MidBand = HighCoFreq - LowCoFreq;
const double QFact = 2.0;
const unsigned int FS = 44100;

void ChangeLowShelf(unsigned int index, double gaindB, double cofreq);

void ChangeHighShelf(unsigned int index, double gaindB, double cofreq);

void ChangePNFilter(unsigned int index, double gaindB, double cofreq);

double GetPNFreq(unsigned int index);

void Filter(double* input, unsigned int filter, unsigned int channel,
            unsigned int inputsize);

}  // namespace EQ

#endif