#include <cmath>
#include <complex>
#include <iostream>

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

int main() {
  typedef std::complex<double> cmplx;
  const cmplx J(0, 1);
  const double PI = 3.1415926536;

  unsigned int len = 8;
  double sig[] = {0.0, 1.0, 1.0, 4.0, 2.0, 1.0, 4.0, 2.0};
  unsigned int flen = len;
  int log2n = std::log2(flen);
  // int log2n = flen;
  cmplx b[flen];

  int n = 1 << log2n;
  for (unsigned int i = 0; i < n; ++i) {
    b[BitReverse(i, log2n)] = sig[i];
  }
  for (int s = 1; s <= log2n; ++s) {
    int m = 1 << s;
    int m2 = m >> 1;
    cmplx w(1, 0);
    cmplx wm = exp(-J * (PI / m2));
    for (int j = 0; j < m2; ++j) {
      for (int k = j; k < n; k += m) {
        cmplx t = w * b[k + m2];
        cmplx u = b[k];
        b[k] = u + t;
        b[k + m2] = u - t;
      }
      w = w * wm;
    }
  }
  for (unsigned int k = 0; k < flen / 2; k++) {
    std::cout << 20 * std::log10(std::abs(b[k])) << "\n";
  }
}