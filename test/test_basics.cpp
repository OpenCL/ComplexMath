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
    namespace bc = boost::compute;
    boost::compute::vector<bc::float_> reals(context);
    boost::compute::vector<bc::float_> imags(context);

    reals.push_back(bc::float_(1.0f), queue);
    reals.push_back(bc::float_(2.0f), queue);
    reals.push_back(bc::float_(-3.0f), queue);
    reals.push_back(bc::float_(4.0f), queue);

    imags.push_back(bc::float_(-1.0f), queue);
    imags.push_back(bc::float_(2.0f), queue);
    imags.push_back(bc::float_(3.0f), queue);
    imags.push_back(bc::float_(-4.0f), queue);

    boost::compute::vector<bc::float2_> complexs(size_t(4), context);

    std::string source = "#include \"clcomplex.h\"\n";
    source += BOOST_COMPUTE_STRINGIZE_SOURCE(        
        __kernel void test_kernel(__global float * reals,
                                  __global float * imags,
                                  __global float2 * complexs)
        {
            const uint i = get_global_id(0);
            complexs[i] = clcomplexf(reals[i], imags[i]);
        }
    );

    std::string options = "-I" + std::string(OPENCL_COMPLEX_MATH_DIR);
    bc::program program = bc::program::build_with_source(
        source, context, options
    );
    bc::kernel k = program.create_kernel("test_kernel");

    k.set_args(
        reals.get_buffer(),
        imags.get_buffer(),
        complexs.get_buffer()
    );

    queue.enqueue_1d_range_kernel(k, 0, complexs.size(), 0).wait();

    BOOST_CHECK_EQUAL(bc::float2_(complexs[0]), bc::float2_(1.0f, -1.0f));
    BOOST_CHECK_EQUAL(bc::float2_(complexs[1]), bc::float2_(2.0f, 2.0f));
    BOOST_CHECK_EQUAL(bc::float2_(complexs[2]), bc::float2_(-3.0f, 3.0f));
    BOOST_CHECK_EQUAL(bc::float2_(complexs[3]), bc::float2_(4.0f, -4.0f));
}

BOOST_AUTO_TEST_SUITE_END()