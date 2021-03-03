#include <iostream>

#include "src/exception.h"
#include "test/tester.h"

int main()
{
	try
	{
		Tester t;
		t.loadTests("test/tests/meta.txt");
		t.loadKernels("test/kernels/meta.txt");
		t.test();
		return 0;
	}
	catch (Exception& e)
	{
		std::cerr << "Exception: " << std::endl;
		std::cerr << e.what() << std::endl;
		return -1;
	}
}