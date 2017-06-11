//
// Created by desk on 6/9/17.
//

#ifndef MACROLESS_H
#define MACROLESS_H

#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

namespace macroless
{

    // Test class.  Also serves as the base class for fixtures.
    class test
    {
    public:

        test(   std::string name,
                std::function<bool(test*)> r,
                std::function<void(test*)> su = [](test*){},
                std::function<void(test*)> td = [](test*){} );

        virtual ~test();

        virtual void setup();
        virtual bool run();
        virtual void teardown();

        std::string test_name_;

        std::function<bool(test*)> run_;
        std::function<void(test*)> setup_, teardown_;
    };

    // Typedefs.
    typedef std::unique_ptr<test> test_ptr;
    typedef std::vector<std::unique_ptr<test>> test_vector;

    // Exception to throw when a test fails.
    class test_fail: std::exception {};

    // Tells where the output goes.
    extern std::ofstream file_output;
    extern bool has_file_output;

    // Get the ostream to output to.
    std::ostream& get_output();

    // Function to run a std::vector of tests.
    bool run(int argc, char** argv, std::function<void()> collector, const test_vector& tests);

    // Message / fail message creation.
    template<typename T>
    void strstr_append(std::stringstream& ss, const T& t){
        ss << t;
    }

    template<typename T, typename... Args>
    void strstr_append(std::stringstream& ss, const T& t, const Args&... args) {
        ss << t << " ";
        strstr_append(ss,args...);
    }

    // Fail message.
    template<typename... Args>
    void fail_test(const Args&... args)
    {
        // Build the message.
        std::stringstream ss;
        ss << "TEST ERROR: ";
        strstr_append(ss,args...);

        // Write the message to the global output.
        get_output() << "\t\t" << ss.str() << "\n";

        // Throw failure exception.
        throw test_fail();
    };

}

#endif //UNTITLED2_MACROLESS_H
