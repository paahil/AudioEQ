#include "EQfilters.hpp"

#include <cmath>

#include "aquila.h"

namespace EQ {
void ChangeLowShelf(unsigned int index, double gaindB, double cofreq) {
  unsigned int FS = 44100;
  const double pi = 3.14159265358979323846;
  const double gain = std::pow(10, (gaindB / 20));
  unsigned int SIZEOWN = Controls.bufferFrames;
  cofreq = (cofreq * 2 * pi) / FS;
  Aquila::SpectrumType filterSpectrum(SIZEOWN);
   for (std::size_t i = 0; i < SIZEOWN; ++i) {
    double f = (double)i / (2 * SIZEOWN);
    // std::cout << "f=" << f * FS << ", ";
    // std::cout << "wc=" << cofreq * FS / (2 * pi) << ", ";
    std::complex<double> b(((std::sqrt(gain) * std::tan(cofreq / 2) + gain) +
                            (std::sqrt(gain) * std::tan(cofreq / 2) - gain) *
                                std::cos(-2 * pi * f)),
                           (std::sqrt(gain) * std::tan(cofreq / 2) - gain) *
                               std::sin(-2 * pi * f));
    std::complex<double> a(
        ((std::sqrt(gain) * std::tan(cofreq / 2) + 1) +
         (std::sqrt(gain) * std::tan(cofreq / 2) - 1) * std::cos(-2 * pi * f)),
        (std::sqrt(gain) * std::tan(cofreq / 2) - 1) * std::sin(-2 * pi * f));
    // std::cout << "a=" << a << ", ";

    filterSpectrum[i] = std::abs(b / a);
    // std::cout << std::abs(filterSpectrum[i]) << std::endl;
  }
  if (index >= Controls.filtspects.size()){
    Controls.filtspects.push_back(filterSpectrum);
    std::cout<<"FWAG";
  } else{
    Controls.filtspects[index] = filterSpectrum;
  }
}

void ChangeHighShelf(unsigned int index, double gaindB, double cofreq){
    unsigned int FS = 44100;
  const double pi = 3.14159265358979323846;
  const double gain = std::pow(10, (gaindB / 20));
  unsigned int SIZEOWN = Controls.bufferFrames;
  cofreq = (cofreq * 2 * pi) / FS;
  Aquila::SpectrumType filterSpectrum(SIZEOWN);
   for (std::size_t i = 0; i < SIZEOWN; ++i) {
    double f = (double)i / (2 * SIZEOWN);
    // std::cout << "f=" << f * FS << ", ";
    // std::cout << "wc=" << cofreq * FS / (2 * pi) << ", ";
    std::complex<double> b(((std::sqrt(gain) * std::tan(cofreq / 2) + gain) +
                            (std::sqrt(gain) * std::tan(cofreq / 2) - gain) *
                                std::cos(-2 * pi * f)),
                           (std::sqrt(gain) * std::tan(cofreq / 2) - gain) *
                               std::sin(-2 * pi * f));
    std::complex<double> a(
        ((std::sqrt(gain) * std::tan(cofreq / 2) + 1) +
         (std::sqrt(gain) * std::tan(cofreq / 2) - 1) * std::cos(-2 * pi * f)),
        (std::sqrt(gain) * std::tan(cofreq / 2) - 1) * std::sin(-2 * pi * f));
    // std::cout << "a=" << a << ", ";

    filterSpectrum[i] = std::abs(b / a);
    // std::cout << std::abs(filterSpectrum[i]) << std::endl;
  }
  if (index > Controls.filtspects.size()){
    Controls.filtspects.push_back(filterSpectrum);
  } else{
    Controls.filtspects[index] = filterSpectrum;
  }
}

Aquila::SpectrumType Filter(Aquila::SpectrumType inputspec, Aquila::SpectrumType filtspec,
                  unsigned int inputsize){
   std::cout<<"Filting";
  unsigned int elecnt = inputsize/sizeof(double);
   std::cout<<elecnt;
  if (elecnt != Controls.bufferFrames){
    return inputspec;
  }
  std::cout<<"Filting";
  std::transform(
        std::begin(inputspec),
        std::end(inputspec),
        std::begin(filtspec),
        std::begin(inputspec),
        [] (Aquila::ComplexType x, Aquila::ComplexType y) { return x * y; }
    );
  return inputspec;
}
   
double* Normalize(double* input, double* filterdata, double gaindB, 
                  unsigned int inputsize){
  //Normalize output
  unsigned int winsize = inputsize / sizeof(double);
  const double gain = std::pow(10, (gaindB / 20));
  double maxorig = input[0];
  double maxfilt = filterdata[0];

  for (unsigned int i = 0; i < winsize; i++){
    if(input[i] > maxorig){
      maxorig = input[i];
    }
    if(filterdata[i] > maxfilt){
      maxfilt = filterdata[i];
    }
  }

  for (unsigned int i = 0; i < winsize; i++){
    filterdata[i] = gain * (maxorig * filterdata[i]/maxfilt);
  }
  
  return filterdata;
}
}  // namespace EQ
