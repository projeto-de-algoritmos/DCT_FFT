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


struct ccomplex* fft(struct ccomplex* x, const size_t N) {
  if (N % 2 > 0) {
    throw std::invalid_argument("Must be a power of 2");
  } else if (N <= 2) {
    return dft(x, N);
  } else {
    size_t k;
    size_t half_N = (size_t) (N/2);

    struct ccomplex* y = (struct ccomplex*) malloc(sizeof(struct ccomplex) * N);
    struct ccomplex* x_even = (struct ccomplex*) malloc(
      sizeof(struct ccomplex) * half_N);
    struct ccomplex* x_odd = (struct ccomplex*) malloc(
      sizeof(struct ccomplex) * half_N);

    for (k = 0; k < N; k += 2) {
      x_even[k].re = x[k].re;
      x_even[k].im = x[k].im;
      x_odd[k+1].re = x[k+1].re;
      x_odd[k+1].im = x[k+1].im;
    }
    x_even = fft(x_even, half_N);
    x_odd = fft(x_odd, half_N);

    size_t k2;
    complex<double> x_odd_k;
    complex<double> x_even_k;
    complex<double> y_k_cpp;
    complex<double> y_k2_cpp;
    for (k = 0; k < (size_t) N/2; k++) {
      x_odd_k = complex<double>(x_odd[k].re, x_odd[k].im);
      x_even_k = complex<double>(x_even[k].re, x_even[k].im);
      y_k_cpp = x_even_k + (x_odd_k * exp(complex<double>(0, -2*M_PI*k/N)));
      y[k].im = y_k_cpp.imag();
      y[k].re = y_k_cpp.real();

      k2 = (size_t) k + N/2;
      y_k2_cpp = x_even_k + (x_odd_k * exp(complex<double>(0, -2*M_PI*k2/N)));
      y[k2].im = y_k2_cpp.imag();
      y[k2].re = y_k2_cpp.real();
    }
    // TODO(leommiranda): dealloc x_even and x_odd
    // for (k = 0; k < (size_t) N/2; k++) {
      // free(x_even[k]);
      // free(x_odd[k]);
    // }
    return y;
  }
}


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
  printf("\n[");
  for (k = 0; k < 128; k++) {
    printf("(%.6lf, %.6lf), ", y[k].re, y[k].im);
  }
  printf("]\n");

  y = fft(x, 128);
  printf("\n[");
  for (k = 0; k < 128; k++) {
    printf("(%.6lf, %.6lf), ", y[k].re, y[k].im);
  }
  printf("]\n");
}
