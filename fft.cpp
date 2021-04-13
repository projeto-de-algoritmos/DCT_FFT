#include "fft.h"
#include <cmath>
#include <cstddef>
#include <vector>
#include <complex>

// #include <cstdio>
#include <memory>

// testing
#include <iostream>
#include "limits.h"

using std::exp;
using std::size_t;
using std::complex;


double** dft(double** x, const size_t N) {
  size_t k;
  size_t n;
  double **y = (double **)malloc(N * sizeof(double *));
  for (k = 0; k < N; k++) {
    y[k] = (double *)malloc(2 * sizeof(double));
  }
  // double y[N][2];
  for (k = 0; k < N; k++) {
    y[k][0] = 0.0;
    y[k][1] = 0.0;
    // y[k].re = 0.0;
    // y[k].im = 0.0;
  }

  for (k = 0; k < N; k++) {
    for (n = 0; n < N; n++) {
      complex<double> num = complex<double>(x[n][0], x[n][1]) *
        exp(complex<double>(0.0, -2*M_PI*k*n/N));
      y[k][0] += num.real();
      y[k][1] += num.imag();
      // y[k].re += num.real();
      // y[k].im += num.imag();
    }
  }
  return y;
}


double** fft(double** x, const size_t N) {
  printf("1");
  if (N % 2 > 0) {
    throw std::invalid_argument("Must be a power of 2");
  } else if (N <= 2) {
    return dft(x, N);
  } else {
    size_t k;
    size_t half_N = (size_t) (N/2);

    printf("1");
    printf("1");
    printf("1");
    printf("1");
    printf("1");
    printf("1");
    double** x_even = (double **)malloc(half_N * sizeof(double *));
    double** x_odd = (double **)malloc(half_N * sizeof(double *));
    double** y_even = (double **)malloc(half_N * sizeof(double *));
    double** y_odd = (double **)malloc(half_N * sizeof(double *));
    for (k = 0; k < half_N; k++) {
      x_even[k] = (double *)malloc(2 * sizeof(double));
      x_odd[k] = (double *)malloc(2 * sizeof(double));
      y_even[k] = (double *)malloc(2 * sizeof(double));
      y_odd[k] = (double *)malloc(2 * sizeof(double));
    }
    printf("1");

    double** y = (double **)malloc(N * sizeof(double *));
    for (k = 0; k < N; k++) {
      y[k] = (double *)malloc(2 * sizeof(double));
    }
    printf("1");

    for (k = 0; k < N; k += 2) {
      x_even[k][0] = x[k][0];
      x_even[k][0] = x[k][0];
      x_odd[k+1][0] = x[k+1][0];
      x_odd[k+1][0] = x[k+1][0];
    }
    y_even = fft(x_even, half_N);
    printf("free(x_even);");
    for (k = 0; k < half_N; k++) {
      free(x_even[k]);
    }
    free(x_even);

    y_odd = fft(x_odd, half_N);
    printf("free(x_odd);");
    for (k = 0; k < half_N; k++) {
      free(x_odd[k]);
    }
    free(x_odd);

    size_t k2;
    complex<double> y_odd_k;
    complex<double> y_even_k;
    complex<double> y_k_cpp;
    complex<double> y_k2_cpp;
    for (k = 0; k < half_N; k++) {
      y_odd_k = complex<double>(y_odd[k][0], y_odd[k][0]);
      y_even_k = complex<double>(y_even[k][0], y_even[k][0]);
      y_k_cpp = y_even_k + (y_odd_k * exp(complex<double>(0, -2*M_PI*k/N)));
      y[k][0] = y_k_cpp.imag();
      y[k][0] = y_k_cpp.real();

      k2 = k + half_N;
      y_k2_cpp = y_even_k + (y_odd_k * exp(complex<double>(0, -2*M_PI*k2/N)));
      y[k2][0] = y_k2_cpp.imag();
      y[k2][0] = y_k2_cpp.real();
    }
    // TODO(leommiranda): dealloc x_even and x_odd
    printf("free(y_even);");
    free(y_even);
    printf("free(y_odd);");
    free(y_odd);
    return y;
  }
}


int main() {
  // double x[128][2];
  size_t k;
  double** y;

  double** x = (double **)malloc(128 * sizeof(double *));
  for (k = 0; k < 128; k++) {
    x[k] = (double *)malloc(2 * sizeof(double));
  }

  // double y[128][2];
  // struct ccomplex* y;
  // ccomplex y[128];

  for (k = 0; k < 128; k++) {
    // random number between 0 and 1
    x[k][0] = ((double) rand() / (INT_MAX));
    // x[k].re = ((double) rand() / (INT_MAX));
    x[k][1] = 0.0;
    // x[k].im = 0.0;
  }

  printf("\n[");
  for (k = 0; k < 128; k++) {
    printf("%.6lf, ", x[k][0]);
    // printf("%.6lf, ", x[k].re);
  }
  printf("]\n");


  // y = dft(x, 128);
  // printf("\n[");
  // for (k = 0; k < 128; k++) {
  //   printf("(%.6lf, %.6lf), ", y[k][0], y[k][1]);
  //   // printf("(%.6lf, %.6lf), ", y[k].re, y[k].im);
  // }
  // printf("]\n");
  // free(y);

  y = fft(x, 128);
  printf("\n[");
  for (k = 0; k < 128; k++) {
    printf("(%.6lf, %.6lf), ", y[k][0], y[k][1]);
  }
  printf("]\n");
  // free(y);
  //
  free(x);
}
