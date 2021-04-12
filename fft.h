#ifdef __cplusplus
extern "C" {
#endif

#include <cstddef>

struct ccomplex {
  double re, im;
};

struct ccomplex* dft(const double* x, const size_t N);
struct ccomplex* fft(const double* x, const size_t N);

#ifdef __cplusplus
}
#endif
