#include "tester.h"

#include "../src/exception.h"
#include "../src/kernelexecutor.h"

#include <sstream>
#include <fstream>

#include <memory>

#include <iostream>

Tester::Tester(): 
    _tests(),
    _kernels()
{
}

Tester::~Tester()
{
}

void Tester::loadTests(const std::string& filepath)
{
    std::ifstream meta(filepath);
    std::stringstream ss;

    if (!meta.is_open()) throw Exception("Unable to read file: " + filepath);

    ss << meta.rdbuf();

    std::string path;

    while (std::getline(ss, path) && path != "")
    {
        loadTest(path);
    }
}

void Tester::loadTest(const std::string& filepath)
{
    std::ifstream test(filepath);
    std::stringstream ss;

    if (!test.is_open()) throw Exception("Unable to read file: " + filepath);

    ss << test.rdbuf();

    int n, k, m;

    ss >> n >> k >> m;

    if (ss.fail()) throw Exception("In file: " + filepath + "\nUnable to read values: n k m");

    Matrix a(n, Vector(k, 0)), b(k, Vector(m, 0)), c(n, Vector(m, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            ss >> a[i][j];
            if (ss.fail()) throw Exception("In file: " + filepath + "\nUnable to read value: a[" + std::to_string(i) + "][" + std::to_string(j) + "]");
        }
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ss >> b[i][j];
            if (ss.fail()) throw Exception("In file: " + filepath + "\nUnable to read value: b[" + std::to_string(i) + "][" + std::to_string(j) + "]");
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ss >> c[i][j];
            if (ss.fail()) throw Exception("In file: " + filepath + "\nUnable to read value: c[" + std::to_string(i) + "][" + std::to_string(j) + "]");
        }
    }

    _tests.push_back(MatrixTest(a, b, c));
}

void Tester::loadKernels(const std::string& filepath)
{
    std::ifstream meta(filepath);
    std::stringstream ss;

    if (!meta.is_open()) throw Exception("Unable to read file: " + filepath);

    ss << meta.rdbuf();

    std::string path;
    std::string name;

    while (std::getline(ss, path) && path != "")
    {
        std::getline(ss, name);

        if (ss.fail()) throw Exception("In file: " + filepath + "\nUnable to read name of kernel");
        loadKernel(path, name);
    }
}

void Tester::loadKernel(const std::string& filepath, const std::string& kernel_name)
{
    std::ifstream meta(filepath);
    std::stringstream ss;

    if (!meta.is_open()) throw Exception("Unable to read file: " + filepath);

    ss << meta.rdbuf();
    
    _kernels.push_back(KernelTest(ss.str(), kernel_name));
}

void Tester::test()
{
    try
    {
        int kernel_number = 1;
        KernelExecutor e;
        e.init();

        for (KernelTest& kernel : _kernels)
        {
            int test_number = 1;

            for (const MatrixTest& test : _tests)
            {
                const int n = test.a().size(), m = test.a()[0].size(), k = test.c()[0].size();
                std::unique_ptr<double[]> a(new double[n * k]), b(new double[k * m]), c(new double[n * m]);

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < k; j++)
                    {
                        a[i * n + j] = test.a()[i][j];
                    }
                }

                for (int i = 0; i < k; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        b[i * k + j] = test.b()[i][j];
                    }
                }

                e.execute(kernel.kernel().c_str(), kernel.name().c_str(), n, m, k, a.get(), b.get(), c.get());

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        if (!nearlyEquals(test.c()[i][j], c[i * n + j]))
                        {
                            std::stringstream ss;

                            ss << "Kernel " << kernel_number << "\n";
                            ss << "Test " << test_number << " failed : c[" << i << "][" << j << "]";
                            ss << " = " << c[i * n + j] << ", expected " << test.c()[i][j];

                            throw Exception(ss.str());
                        }
                    }
                }

                std::cout << "Kernel " << kernel_number << " ";
                std::cout << "Test " << test_number << " - passed" << std::endl;

                test_number++;
            }

            kernel_number++;
        }
    }
    catch (cl::Error& e)
    {
        throw Exception(std::string("OpenCl error:\n") + e.what() + "\nErr code = " + std::to_string(e.err()));
    }
}
