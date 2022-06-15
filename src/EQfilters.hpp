#ifndef EQ_FILTERSHPP
#define EQ_FILTERSHPP
#include <iostream>
#include <vector>

#include "EQcontrols.hpp"

namespace EQ {
void ChangeLowShelf(unsigned int index, double gaindB, double cofreq);

void ChangeHighShelf(unsigned int index, double gaindB, double cofreq);

void ChangePNFilter(unsigned int index, double gaindB, double cofreq);

void Filter(double* inputspec, unsigned int filter, unsigned int channel, unsigned int inputsize);

void Scale(double* input, double gaindB, unsigned int inputsize);
}  // namespace EQ

#endif