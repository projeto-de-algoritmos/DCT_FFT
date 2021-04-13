import numpy as np


# method from:
# https://towardsdatascience.com/fast-fourier-transform-937926e591cb
def dft(x):
    x = np.asarray(x, dtype=float)
    N = x.shape[0]
    n = np.arange(N)
    k = n.reshape((N, 1))
    M = np.exp(-2j * np.pi * k * n / N)
    return np.dot(M, x)


# method from:
# https://towardsdatascience.com/fast-fourier-transform-937926e591cb
def fft(x):
    x = np.asarray(x, dtype=float)
    N = x.shape[0]
    if N % 2 > 0:
        raise ValueError("must be a power of 2")
    elif N <= 2:
        return dft(x)
    else:
        X_even = fft(x[::2])
        X_odd = fft(x[1::2])
        terms = np.exp(-2j * np.pi * np.arange(N) / N)
        return np.concatenate([X_even + terms[:int(N/2)] * X_odd,
                               X_even + terms[int(N/2):] * X_odd])


# adapted method
def discrete_fourier_transform(x):
    # easier to transfer to C/C++
    x = np.asarray(x, dtype=float)
    N = len(x)
    x_result = np.zeros(N, dtype='complex_')
    for k in range(N):
        for n in range(N):
            x_result[k] += x[n]*np.exp(-2j * np.pi * k * n / N)
    return x_result


# adapted method
def fast_fourier_transform(x):
    # easier to transfer to C/C++
    x = np.asarray(x, dtype=float)
    N = len(x)
    if N % 2 > 0:
        raise ValueError("must be a power of 2")
    elif N <= 2:
        return discrete_fourier_transform(x)
    else:
        x_result = np.empty(N, dtype='complex_')
        x_even = fast_fourier_transform(x[0::2])
        x_odd = fast_fourier_transform(x[1::2])
        # prob. just a ridiculous micro optimization
        for k in range(0, int(N/2)):
            x_result[k] = x_even[k] + (x_odd[k] * np.exp(-2j * np.pi * k / N))
            # another ridiculous micro optimization
            k2 = int(k + N/2)
            x_result[k2] = x_even[k] + (
                x_odd[k] * np.exp(-2j * np.pi * k2 / N)
            )
        return x_result


if __name__ == "__main__":
    x = np.random.random(1024)
    a = dft(x)
    b = discrete_fourier_transform(x)
    c = fft(x)
    d = fast_fourier_transform(x)
    e = np.fft.fft(x)
    assert np.allclose(a, b)
    assert np.allclose(a, c)
    assert np.allclose(a, d)
    assert np.allclose(a, e)
