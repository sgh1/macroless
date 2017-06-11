//
// Created by desk on 6/9/17.
//

#include "macroless.h"

#include <fstream>
#include <iomanip>

namespace macroless
{
    // Initialize globals.
    bool has_file_output = false;
    std::ofstream file_output;



    test::test( std::string name,
                std::function<bool(test*)> r,
                std::function<void(test*)> su,
                std::function<void(test*)> td):
        test_name_( name),
        run_(       r),
        setup_(     su),
        teardown_(  td)
    {
    }

    test::~test(){

    }

    void test::setup() {
        this->setup_(this);
    }

    bool test::run() {
        return this->run_(this);
    }

    void test::teardown() {
        this->teardown_(this);
    }

    // Function to run a std::vector of tests.
    bool run(int argc, char** argv, std::function<void()> collector,
             const test_vector& tests)
    {
        // The test name is the binary name.
        // Parse command line arguments.  If a second arg exists, we use it as the filename for output.
        std::string test_name;

        if(argc > 0) {
            test_name = std::string(argv[0]);
        }

        if(argc > 1){
            file_output = std::ofstream(argv[1]);
            has_file_output = true;
        }

        // Run the collector.
        collector();

        // Get total tests.
        size_t n_tests = tests.size();
        size_t tests_passed = 0;

        get_output() << "\n====== Starting test " << test_name << " ============\n\n";

        // Run the tests.
        for(auto& t : tests)
        {
            // This try/catch will only catch test failures.
            try
            {
                t->setup();

                // Run the test.
                if(t->run()){
                    tests_passed++;
                    get_output() << "\tTest case " << std::setw(30) << std::left <<  t->test_name_ << " [PASSED].\n";
                }

                t->teardown();
            }

            // Catch test failure.
            catch(test_fail& tf)
            {
                get_output() << "\tTest case " << std::setw(30) << std::left <<  t->test_name_ << " [FAILED].\n";
                t->teardown();
            }
        }

        // Create summary.
        get_output() << "\n========== Test Complete ==========\n";
        get_output() << n_tests << " tests ran, " << tests_passed << " tests passed, " << n_tests-tests_passed << " tests failed.\n";
        get_output() << "====================================\n";

        return tests_passed == n_tests;
    }

    // Get the ostream to output to.
    std::ostream& get_output()
    {
        if(has_file_output){
            return file_output;
        }

        return std::cout;
    }

}