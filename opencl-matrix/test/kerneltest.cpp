#include "kerneltest.h"

KernelTest::KernelTest(const std::string& kernel, const std::string& name):
    _kernel(kernel),
    _name(name)
{
}

KernelTest::KernelTest(const KernelTest& other):
    _kernel(other._kernel),
    _name(other._name)
{
}

KernelTest::KernelTest(KernelTest&& other) noexcept:
    _kernel(std::move(other._kernel)),
    _name(std::move(other._name))
{
}

KernelTest::~KernelTest()
{
}

const std::string& KernelTest::kernel() const
{
    return _kernel;
}

const std::string& KernelTest::name() const
{
    return _name;
}
