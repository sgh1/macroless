

#include "macroless.h"

#include <map>

// Do some tests on std::map.  We also take a look at text fixtures and a way to accomplish
// similar functionality just using the lambdas.

// Create test case vector for this test.
macroless::test_vector tests;

// Create something like a normal test-fixture.
// Test class.  Also serves as the base class for fixtures.
class map_test_fixture : public macroless::test
{
public:

    map_test_fixture(   std::string name,
                        std::function<bool(macroless::test*)> r,
                        std::function<void(macroless::test*)> su = [](macroless::test*){},
                        std::function<void(macroless::test*)> td = [](macroless::test*){}):
            macroless::test(name, r, su, td)
    {
    }

    virtual void setup()
    {
        macroless::get_output() << "\t\tSetting up map_test_fixture...\n";

        my_map_[4] = "C++";
        my_map_[-64] = "D";
        my_map_[0] = "Rust";

        macroless::test::setup();
    }
    virtual void teardown()
    {
        macroless::get_output() << "\t\tTearing down map_test_fixture...\n";

        macroless::test::teardown();
    }

    std::map<int,std::string> my_map_;
};

// Create collection function.
void std_map_tests()
{

    // Create test cases and add them to the test vector.
    // Test size of a vector.
    tests.push_back(
            macroless::test_ptr(
                    new map_test_fixture(
                            "map_size_check",
                            [](macroless::test* tst)
                            {
                                // We know we're dealing with a map_test_fixture here, so
                                // cast it.  A little more boilerplate...  We also have an additional
                                // level of indirection w.r.t. most testing frameworks.

                                map_test_fixture* this_tst =
                                        dynamic_cast<map_test_fixture*>(tst);

                                 if(this_tst->my_map_.size() != 3) {
                                     macroless::fail_test("my_map.size() != 3.");
                                 }

                                return true;
                            }
                    )));


    // Here's another similar idea to a fixture...

    // Create some big persistent resources.
    std::map<int, std::string> my_big_map;
    my_big_map[1] = "Oberon";
    my_big_map[18] = "Two Hearted";
    my_big_map[-1] = "Oarsman";

    // Test with my_big_map as capture.
    // TODO: there is a segfault here if my_big_map is captured by ref.
    // Need to think more?
    tests.push_back(
            macroless::test_ptr(
                    new macroless::test(
                            "check_for_key_28",
                            [my_big_map](macroless::test*)
                            {
                                if (my_big_map.find(28) == my_big_map.end()){
                                    macroless::fail_test("Key value 28 was not found in the map.");
                                }

                                // If we get here, we pass the test.
                                return true;
                            }
                    )));


    // Test with my_big_map as capture.
    tests.push_back(
            macroless::test_ptr(
                    new macroless::test(
                            "check_1_is_oberon",
                            [my_big_map](macroless::test*)
                            {
                                if (my_big_map.at(1) != "Oberon"){
                                    macroless::fail_test("my_big_map[1] != Oberon.");
                                }

                                // If we get here, we pass the test.
                                return true;
                            }
                    )));


}

// Entry point for test.
int main(int argc, char** argv) {
    return macroless::run(argc,argv,std_map_tests,tests);
}

