// =====================================================================================
// Exercises_11_Initialization.cpp
// =====================================================================================


#include "../LoggerUtility/ScopedTimer.h"

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <string_view>
#include <print>

namespace Exercises_Initialization {

    namespace Exercise_02 {

        class SomeStrings
        {
        public:
            static auto transferData(const std::vector<std::string>& strings)
            {
                // prevent optimizer to work too hard ...
                auto& first = strings.front();
                auto& last = strings.back();
                return first + last;
                //std::cout << "first=" << first << std::endl;
                //std::cout << "last=" << last << std::endl;
            }

            static auto transferData(const std::initializer_list<std::string> strings)
            {
                // prevent optimizer to work too hard ...
                const auto& first = strings.begin();
                const auto& last = std::prev(strings.end());
                return *first + *last;
                //std::cout << "first=" << *first << std::endl;
                //std::cout << "last=" << *last << std::endl;
            }
        };

        // Note: Debug vs Release Mode
        constexpr int MaxIteration = 10'000'000;

        static void testExercise_02() {
            {
                ScopedTimer watch{};

                for (size_t i{}; i != MaxIteration; ++i) {

                    // heap-based transfer of strings
                    // Kleine Zeichenketten // SSO
                    SomeStrings::transferData(
                        std::vector<std::string> {
                        "A", "B", "C", "D", "E", "F", "G", "H", "I",
                            "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                            "S", "T", "U", "V", "W", "X", "Y", "Z"
                    });
                }

                std::cout << "std::vector: " << std::endl;
            }

            {
                ScopedTimer watch{};

                for (size_t i{}; i != MaxIteration; ++i) {

                    // stack-based transfer of strings
                    SomeStrings::transferData(
                        std::initializer_list<std::string> {
                        "A", "B", "C", "D", "E", "F", "G", "H", "I",
                            "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                            "S", "T", "U", "V", "W", "X", "Y", "Z"
                    });
                }

                std::cout << "std::initializer_list: " << std::endl;;
            }
        }
    }
}

void test_initializer_list()
{
    using namespace Exercises_Initialization;
    Exercise_02::testExercise_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================