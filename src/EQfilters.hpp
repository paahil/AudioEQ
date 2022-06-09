#ifndef EQ_FILTERSHPP
#define EQ_FILTERSHPP
#include <iostream>
#include <vector>
#include "EQcontrols.hpp"

namespace EQ {
void ChangeLowShelf(unsigned int index, double gaindB, double cofreq);

void ChangeHighShelf(unsigned int index, double gaindB, double cofreq);

void ChangePNFilter(unsigned int index, double gaindB, double cofreq);

Aquila::SpectrumType Filter(Aquila::SpectrumType inputspec, Aquila::SpectrumType filterspec,
                  unsigned int inputsize);

double* Normalize(double* input, double* filterdata, double gaindB, 
                  unsigned int inputsize);
}  // namespace EQ

#endif