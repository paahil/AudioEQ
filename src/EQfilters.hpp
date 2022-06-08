#ifndef EQ_FILTERSHPP
#define EQ_FILTERSHPP
#include <iostream>
#include <vector>
namespace EQ {
double* LowShelf(double* filterdata, double gaindB, double cofreq,
                 unsigned int inputsize);

double* HighShelf(double* filterdata, double gaindB, double cofreq,
                  unsigned int inputsize);
}  // namespace EQ

#endif