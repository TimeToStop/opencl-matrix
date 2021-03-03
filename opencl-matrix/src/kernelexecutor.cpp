#include "kernelexecutor.h"

#include <chrono>

#include "exception.h"

#include <iostream>

KernelExecutor::KernelExecutor():
    _main_device()
{
}

KernelExecutor::~KernelExecutor()
{
}

void KernelExecutor::init()
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    if (platforms.size() == 0)
    {
        throw  Exception("No platforms found. Check CUDA installation");
    }

    cl::Platform platform = platforms[0];

    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

    if (devices.size() == 0)
    {
        throw Exception("No devices found");
    }

    _main_device = devices[0];
}

ms_time KernelExecutor::execute(const char* kernel_src, const char* kernel_name, const int n, const int k, const int m, const double* a, const double* b, double* c)
{
    cl::Context context(_main_device);
    cl::CommandQueue queue(context, _main_device);

    cl::Buffer inputMatrixA(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, n * k * sizeof(double), (void*)a);
    cl::Buffer inputMatrixB(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, k * m * sizeof(double), (void*)b);
    cl::Buffer outputMatrixC(context, CL_MEM_READ_WRITE, n * m * sizeof(double));

    cl::Program::Sources source(1, { kernel_src, strlen(kernel_src) + 1 });
    cl::Program program(context, source);

    program.build();

    cl::Kernel kernel(program, kernel_name);

    int arg = 0;

    kernel.setArg(arg++, n);
    kernel.setArg(arg++, k);
    kernel.setArg(arg++, m);

    kernel.setArg(arg++, inputMatrixA);
    kernel.setArg(arg++, inputMatrixB);
    kernel.setArg(arg++, outputMatrixC);

    auto start = std::chrono::high_resolution_clock::now();

    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(16 * (n/16 + 1), 16*(m/16 + 1)), cl::NDRange(16, 16));
    queue.finish();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    queue.enqueueReadBuffer(outputMatrixC, CL_TRUE, 0, n * m * sizeof(double), (void*)c);

    return duration.count();
}
