#pragma once

#include "matrixtest.h"
#include "kerneltest.h"

#include <list>
#include <string>

class Tester
{
public:
	Tester();
	~Tester();

	void loadTests(const std::string& filepath);
	void loadTest(const std::string& filepath);

	void loadKernels(const std::string& filepath);
	void loadKernel(const std::string& filepath, const std::string& kernel_name);

	void test();

private:
	std::list<MatrixTest> _tests;
	std::list<KernelTest> _kernels;
};

