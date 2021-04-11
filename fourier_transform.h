#include <complex>
#include <cstddef>
#include <vector>
using std::complex;
using std::exp;
using std::size_t;
using std::vector;

vector<complex<double>> discrete_fourier_transform(const vector<complex<double>> &input)
{
    vector<complex<double>> output;
    size_t n = input.size();
    for (size_t k = 0; k < n; k++)
    {
        complex<double> sum(0, 0);
        for (size_t t = 0; t < n; t++)
        {
            double angle = 2 * M_PI * k * t / n;
            sum += input[t] * exp(complex<double>(0, -angle));
        }
        output.push_back(sum);
    }
    return output;
}

vector<complex<double>> fast_fourier_transform(const vector<complex<double>> &input)
{
    vector<complex<double>> output;
    size_t n = input.size();

    if (n % 2 > 0)
    {
        throw std::invalid_argument("Must be a power of 2");
    }
    else if (n <= 2)
    {
        return discrete_fourier_transform(input);
    }
    else
    {
        vector<complex<double>> even = fast_fourier_transform(input); // need to find out to to inplement [y::x]
        vector<complex<double>> odd = fast_fourier_transform(input);  // need to find out to to inplement [y::x]

        for (size_t k = 0; k < int(n / 2); k++)
        {
            double angle = 2 * M_PI * k / n;
            complex<double> right = odd[k] * exp(complex<double>(0, -angle));
            output[k] = even[k] + right;

            size_t k2 = int(k + int(n / 2));
            double angle2 = 2 * M_PI * k2 / n;
            complex<double> right = odd[k] * exp(complex<double>(0, -angle2));
            output[k2] = even[k] + right;
        }
    }

    return output;
}