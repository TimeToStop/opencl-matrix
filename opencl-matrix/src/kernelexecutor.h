#pragma once

#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>

#include "matrix.h"

using ms_time = unsigned long long;

class KernelExecutor
{
public:
	KernelExecutor();
	~KernelExecutor();

	void init();

	ms_time execute(const char* kernel_src, const char* kernel_name, const int n, const int k, const int m, const double* a, const double* b, double* c);

private:
	cl::Device _main_device;
};

