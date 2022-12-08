#ifndef EQ_FILTERSHPP
#define EQ_FILTERSHPP
#include <iostream>
#include <vector>

#include "EQcontrols.hpp"

namespace EQ {
void ChangeLowShelf(EQControls* cntrls, unsigned int index, double gaindB,
                    double cofreq);

void ChangeHighShelf(EQControls* cntrls, unsigned int index, double gaindB,
                     double cofreq);

void ChangePNFilter(EQControls* cntrls, unsigned int index, double gaindB,
                    double cofreq);

void Filter(EQControls* cntrls, double* input, unsigned int filter,
            unsigned int channel, unsigned int inputsize);

}  // namespace EQ

#endif