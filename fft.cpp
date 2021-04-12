#include "fft.h"
#include <cmath>
#include <cstddef>
#include <vector>
#include <complex>

// testing
#include <iostream>
#include "limits.h"

using std::exp;
using std::size_t;
// using std::vector;
using std::complex;


struct ccomplex* dft(const double* x, const size_t N) {
  struct ccomplex* y = (struct ccomplex*) malloc(sizeof(struct ccomplex) * N);
  size_t k;
  size_t n;

  for (k = 0; k < N; k++) {
    y[k].re = 0.0;
    y[k].im = 0.0;
  }

  for (k = 0; k < N; k++) {
    for (n = 0; n < N; n++) {
      std::complex<double> num = x[n] * std::exp(
        std::complex<double>(0.0, -2*M_PI*k*n/N));
      y[k].re += num.real();
      y[k].im += num.imag();
    }
  }
  return y;
}


// void fft(const double* x, ccomplex* y, const size_t N) {
//   if (N % 2 > 0) {
//     throw std::invalid_argument("Must be a power of 2");
//   } else if (N <= 2) {
//     return dft(x);
//   } else {
//     creal_T* y;
//     // TODO(leommiranda): separate x into odds and evens
//     creal_T* x_even = fft(x);
//     creal_T* x_odd = fft(x);
//     size_t k;
//     size_t k2;
//     for (k = 0; k < (int) floor(N/2); k++) {
//       y[k] = x_even[k] + (x_odd[k] * exp(complex<double>(0, -2*M_PI*k/N)));
//       k2 = (int) floor(k + N/2);
//       y[k2] = x_even[k] + (x_odd[k] * exp(complex<double>(0, -2*M_PI*k2/N)));
//     }
//   }
//
//   return output;
// }


int main() {
  double x[128];
  struct ccomplex* y;
  // ccomplex y[128];

  size_t k;
  for (k = 0; k < 128; k++) {
    // random number between 0 and 1
    x[k] = ((double) rand() / (INT_MAX));
  }

  printf("\n[");
  for (k = 0; k < 128; k++) {
    printf("%lf, ", x[k]);
  }
  printf("]\n");
  printf("\n\n\n");

  y = dft(x, 128);
  // memcpy(&track->sig[0], &det->sig[0], 300U * sizeof(double));
  // memcpy(y[0], dft(x, 128)[0], 5 * sizeof *arr);

  printf("\n[");
  for (k = 0; k < 128; k++) {
    printf("(%.6lf, %.6lf), ", y[k].re, y[k].im);
  }
  printf("]\n");
}
