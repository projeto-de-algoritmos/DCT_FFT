#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif


// struct ccomplex {
//   double re, im;
// };

double** dft(double** x, const size_t N);
double** fft(double** x, const size_t N);
// struct ccomplex* dft(const struct ccomplex* x, const size_t N);
// struct ccomplex* fft(const struct ccomplex* x, const size_t N);

#ifdef __cplusplus
}
#endif
