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

#define fname(name, sufix) cl##name##sufix

// float2
#define clrealf(complex) complex.x;
#define climagf(complex) complex.y;

// double2
#define clreal(complex) complex.x;
#define climag(complex) complex.y;

#define OPENCL_COMPLEX_MATH_FUNCS(complex_type, real_type, func_sufix) \
    complex_type fname(complex, func_sufix)(real_type r, real_type i) \
    { \
        return (complex_type)(r, i); \
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

#undef fname
#endif // OPENCL_COMPLEX_MATH