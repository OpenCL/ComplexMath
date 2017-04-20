//---------------------------------------------------------------------------//
// MIT License
//
// Copyright (c) 2017 StreamComputing
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------//

#ifndef OPENCL_COMPLEX_MATH
#define OPENCL_COMPLEX_MATH

#define CONCAT(x, y) x##y
#define FNAME(name, sufix) c##name##sufix

// float2
#define clrealf(complex) complex.x;
#define climagf(complex) complex.y;

// double2
#define clreal(complex) complex.x;
#define climag(complex) complex.y;

#define OPENCL_COMPLEX_MATH_FUNCS(complex_type, real_type, func_sufix) \
    complex_type CONCAT(complex, func_sufix)(real_type r, real_type i) \
    { \
        return (complex_type)(r, i); \
    } \
    complex_type FNAME(add, func_sufix)(complex_type x, complex_type y) \
    { \
        return x + y; \
    } \
    \
    complex_type FNAME(sub, func_sufix)(complex_type x, complex_type y) \
    { \
        return x - y; \
    } \
    \
    real_type FNAME(abs, func_sufix)(complex_type z) \
    { \
        return length(z); \
    } \
    \
    real_type FNAME(arg, func_sufix)(complex_type z) \
    { \
        return atan2(z.y, z.x); \
    } \
    \
    complex_type FNAME(conj, func_sufix)(complex_type z) \
    { \
        return (complex_type)(z.x, -z.y); \
    } \
    \
    complex_type FNAME(proj, func_sufix)(complex_type z) \
    { \
        if(isinf(z.x) || isinf(z.y)) \
        { \
            return (complex_type)(INFINITY, (copysign(0.0f, z.y))); \
        } \
        return z; \
    } \
    \
    complex_type FNAME(exp, func_sufix)(complex_type z) \
    { \
        /* The complex exponential function e^z for z = x+i*y */ \
        /* equals to e^x * cis(y), */ \
        /* or, e^x * (cos(y) + i*sin(y)) */ \
        real_type expx = exp(z.x); \
        return (complex_type)(expx * cos(z.y), expx * sin(z.y)); \
    } \
    \
    complex_type FNAME(log, func_sufix)(complex_type z) \
    { \
        /* log(z) = log(abs(z)) + i * arg(z)  */ \
        return (complex_type)(log(CONCAT(cabs, func_sufix)(z)),CONCAT(carg, func_sufix)(z)); \
    }

// float complex
typedef float2 cfloat;
OPENCL_COMPLEX_MATH_FUNCS(float2, float, f)

// double complex
#ifdef cl_khr_fp64
#   ifdef OPENCL_COMPLEX_MATH_USE_DOUBLE
#       pragma OPENCL EXTENSION cl_khr_fp64 : enable
        typedef double2 cdouble;
        OPENCL_COMPLEX_MATH_FUNCS(double2, double,)
#   endif
#endif

#undef FNAME
#undef CONCAT
#endif // OPENCL_COMPLEX_MATH