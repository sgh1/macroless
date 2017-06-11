# macroless C++ testing

This is just a little experiment in creating a C++ testing framework that doesn't use macros.  

I think the use of macros in some of the more popular C++ testing frameworks is justified, and I've used a few such frameworks effectively.  I just thought I'd see what a native C++ framework might look like.

Here's an example test:


	#include "macroless.h"

	#include <vector>

	// Do some tests on std::vector.

	// Create test case vector for this test.
	macroless::test_vector tests;

	// Create collection function.
	void std_vector_tests()
	{

		// Create test cases and add them to the test vector.
		// Test size of a vector.
		tests.push_back(
			macroless::test_ptr(
				new macroless::test(
					"size_check",
					[](macroless::test*)
					{
						// Create std vector.
						std::vector<int> int_vector;

						// Add some items.
						int_vector.push_back(1);
						int_vector.push_back(-15);
						int_vector.push_back(21);

						// Do the test.
						if(int_vector.size() != 3){
							macroless::fail_test("The size of int_vector is",int_vector.size(),
												 "but it should have been 3.");
						}

						// If we get here, we pass the test.
						return true;
					}
				)));

		// Test value of a vector.
		tests.push_back(
			macroless::test_ptr(
				new macroless::test(
					"value_check",
					[](macroless::test*)
					{
						// Create std vector.
						std::vector<int> int_vector;

						// Add some items.
						int_vector.push_back(1);
						int_vector.push_back(-15);
						int_vector.push_back(21);

						// Do the test.
						if(int_vector[1] != 3){
							macroless::fail_test("int_vector[2] was",int_vector[1],
												 "but it should have been 3.");
						}

						// If we get here, we pass the test.
						return true;
					}
				)));

		// Test value of a vector again.
		tests.push_back(
			macroless::test_ptr(
				new macroless::test(
					"value_check_2",
					[](macroless::test*)
					{
						// Create std vector.
						std::vector<int> int_vector;

						// Add some items.
						int_vector.push_back(1);
						int_vector.push_back(-15);
						int_vector.push_back(21);

						// Do the test.
						if(int_vector[2] != 21){
							macroless::fail_test("int_vector[2] was",int_vector[2],
												 "but it should have been 21.");
						}

						// If we get here, we pass the test.
						return true;
					}
				)));

	}

	// Entry point for test.
	int main(int argc, char** argv) {
		return macroless::run(argc,argv,std_vector_tests,tests);
	}

