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
using std::complex;


struct ccomplex* dft(struct ccomplex* x, const size_t N) {
  struct ccomplex* y = (struct ccomplex*) malloc(sizeof(struct ccomplex) * N);
  size_t k;
  size_t n;

  for (k = 0; k < N; k++) {
    y[k].re = 0.0;
    y[k].im = 0.0;
  }

  for (k = 0; k < N; k++) {
    for (n = 0; n < N; n++) {
      complex<double> num = complex<double>(x[n].re, x[n].im) *
        exp(complex<double>(0.0, -2*M_PI*k*n/N));
      y[k].re += num.real();
      y[k].im += num.imag();
    }
  }
  return y;
}


// struct ccomplex* fft(struct ccomplex* x, const size_t N) {
//   if (N % 2 > 0) {
//     throw std::invalid_argument("Must be a power of 2");
//   } else if (N <= 2) {
//     return dft(x, N);
//   } else {
//     struct ccomplex* y = (struct ccomplex*) malloc(sizeof(struct ccomplex) * N);
//     struct ccomplex* x_even = (struct ccomplex*) malloc(
//       sizeof(struct ccomplex) * N/2);
//     struct ccomplex* x_odd = (struct ccomplex*) malloc(
//       sizeof(struct ccomplex) * N/2);
//
//     for (k = 0; k < N; k += 2) {
//       x_even[k] = complex<double>(x[k].re, x[k].im);
//       x_odd[k+1] = complex<double>(x[k+1].re, x[k+1].im);
//       // x_odd[k+1] = x[k+1];
//     }
//     // TODO(leommiranda): separate x into odds and evens
//     x_even = fft(x_even, N);
//     x_odd = fft(x_odd, N);
//     size_t k;
//     size_t k2;
//     for (k = 0; k < (size_t) N/2; k++) {
//       y[k] = x_even[k] + (x_odd[k] * exp(complex<double>(0, -2*M_PI*k/N)));
//       k2 = (size_t) k + N/2;
//       y[k2] = x_even[k] + (x_odd[k] * exp(complex<double>(0, -2*M_PI*k2/N)));
//     }
//     return y;
//   }
// }


int main() {
  struct ccomplex* x = (struct ccomplex*) malloc(sizeof(struct ccomplex) * 128);
  struct ccomplex* y;
  // ccomplex y[128];

  size_t k;
  for (k = 0; k < 128; k++) {
    // random number between 0 and 1
    x[k].re = ((double) rand() / (INT_MAX));
    x[k].im = 0.0;
  }

  y = dft(x, 128);
  // memcpy(&track->sig[0], &det->sig[0], 300U * sizeof(double));
  // memcpy(y[0], dft(x, 128)[0], 5 * sizeof *arr);

  printf("\n[");
  for (k = 0; k < 128; k++) {
    printf("(%.6lf, %.6lf), ", y[k].re, y[k].im);
  }
  printf("]\n");
}
