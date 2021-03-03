#pragma once
#include <string>

class KernelTest
{
public:
	KernelTest(const std::string& kernel, const std::string& name);
	KernelTest(const KernelTest& other);
	KernelTest(KernelTest&& other) noexcept;
	~KernelTest();

	const std::string& kernel() const;
	const std::string& name() const;

private:
	std::string _kernel;
	std::string _name;
};

