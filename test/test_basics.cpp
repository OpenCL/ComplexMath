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

#define BOOST_TEST_MODULE TestBasics
#include <boost/test/unit_test.hpp>

#include <complex>

#include <boost/compute/core.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/container/vector.hpp>

struct OpenCLContext 
{
    boost::compute::device        device;
    boost::compute::context       context;
    boost::compute::command_queue queue;

    OpenCLContext() :
        device (boost::compute::system::default_device()),
        context(boost::compute::system::default_context()),
        queue  (boost::compute::system::default_queue())
    {}
};

BOOST_FIXTURE_TEST_SUITE(complex_numbers_test, OpenCLContext)

BOOST_AUTO_TEST_CASE(test_create)
{

}

BOOST_AUTO_TEST_SUITE_END()