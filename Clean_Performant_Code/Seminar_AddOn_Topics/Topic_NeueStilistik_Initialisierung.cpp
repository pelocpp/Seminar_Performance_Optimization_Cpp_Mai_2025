



#include <algorithm>
#include <numeric>
#include <array>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <string_view>
#include <print>
#include <execution>

namespace Algorithms {

    class Foo {
    public:
        Foo() = default;
        Foo(int) {};
    };

    static Foo createFooOject() { return {}; }

    // links - nach - rechts
    void new_init_syntax() {

        auto z = 123;
        int z1 = 123;

        auto var1 = 0;
        auto var2 = Foo{};
        auto var3 = createFooOject();
        auto var4 = std::mutex{};

        auto name = std::string{ "Hans" };
        auto anotherName = "Sepp";

        auto ptr = std::make_unique<Foo>(123);

        auto myLambda = [](auto n, auto m) { return n + m; };


    }

}

