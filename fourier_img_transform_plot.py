clear
clear
clear
python3
import numpy as np


# fast discrete fourier transform of a vector
# the implementation is slow
# method from https://towardsdatascience.com/fast-fourier-transform-937926e591cb
def dft(x):
    x = np.asarray(x, dtype=float)
    N = x.shape[0]
    n = np.arange(N)
    k = n.reshape((N, 1))
    M = np.exp(-2j * np.pi * k * n / N)
    return np.dot(M, x)


# method from https://towardsdatascience.com/fast-fourier-transform-937926e591cb
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

minus2j_times_pi = -2j * np.pi

# my method
def discrete_fourier_transform(x):
    # transferable to C++
    # but requires dealing with complex numbers
    # and it would be good to do some dethrashing
    x = np.asarray(x, dtype=float)
    N = len(x)    
    x_result = np.zeros(N, dtype='complex_')
    for k in range(N):
        for n in range(N):
            x_result[k] += x[n]*np.exp(minus2j_times_pi * k * n / N)
    return x_result


# my method
def fast_fourier_transform(x):
    # transferable to C++
    # but requires dealing with complex numbers
    # and it would be good to do some dethrashing
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
            x_result[k] = x_even[k] + (x_odd[k] * np.exp(minus2j_times_pi * k / N ))
            # another ridiculous micro optimization
            k2 = int(k + N/2)
            x_result[k2] = x_even[k] + (x_odd[k] * np.exp(minus2j_times_pi * k2 / N ))
        return x_result



x = np.random.random(1024)
dft(x)
discrete_fourier_transform(x)
fft(x)
fast_fourier_transform(x)
np.fft.fft(x)



# naive_fourier_transform(0, 0, 0.14)
# naive_fourier_transform(110, 120, 0.55)
# naive_fourier_transform(1, 1, 0.97)
# naive_fourier_transform(1, 0, 0.11)


###############################################################################################


clear
clear
clear
python3
import numpy as np
import cv2
import time

# u, v = (1.15, -0.99)
# u, v = (10.0, -5.0)
u, v = (0.0, 0.04)

def fourier_transform_real_component(x, y):
    return np.cos(2*np.pi*(u*x + v*y))

def fourier_transform_imag_component(x, y):
    return np.sin(2*np.pi*(u*x + v*y))

h,w = (300, 300)

def myimg(comp):
    img = np.empty((h,w), dtype=np.float32)
    for x in range(w):
        for y in range(h):
            r = comp(y, x)
            img[x,y] = 1.0- ((1.0 + r) / 2.0)
    img = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
    return img

re_img = myimg(fourier_transform_real_component)
im_img = myimg(fourier_transform_imag_component)

cv2.imshow('real img', re_img)
cv2.imshow('imag img', im_img)

sum_img = np.ones((h,w,3), dtype=np.float32)
for x in range(w):
    for y in range(h):
        sum_img[x][y] = re_img[x][y][0] + im_img[x][y][0]

cv2.imshow('sum img', sum_img)

time.sleep(0.2)
cv2.waitKey(50)

cv2.destroyAllWindows()

# continuous transform
def continuous_naive_fourier_transform(x, y, signal):
    calc_1 = 2*np.pi*(u*x + v*y)
    re = np.cos(calc_1)
    calc_2 = np.dot(re, signal)
    im = np.complex(imag=1)*np.sin(calc_1)
    calc_3 = np.dot(im, signal)
    result = calc_2 + calc_3
    return result

